#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;
struct sk_psock {size_t cork_bytes; int /*<<< orphan*/  eval; struct sk_msg* cork; } ;
struct sk_msg {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __SK_NONE ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,size_t) ; 
 int sk_msg_full (struct sk_msg*) ; 
 int /*<<< orphan*/  sk_msg_init (struct sk_msg*) ; 
 int /*<<< orphan*/  sk_msg_page_add (struct sk_msg*,struct page*,size_t,int) ; 
 struct sk_psock* sk_psock_get (struct sock*) ; 
 int /*<<< orphan*/  sk_psock_put (struct sock*,struct sk_psock*) ; 
 int tcp_bpf_send_verdict (struct sock*,struct sk_psock*,struct sk_msg*,int*,int) ; 
 int tcp_sendpage (struct sock*,struct page*,int,size_t,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcp_bpf_sendpage(struct sock *sk, struct page *page, int offset,
			    size_t size, int flags)
{
	struct sk_msg tmp, *msg = NULL;
	int err = 0, copied = 0;
	struct sk_psock *psock;
	bool enospc = false;

	psock = sk_psock_get(sk);
	if (unlikely(!psock))
		return tcp_sendpage(sk, page, offset, size, flags);

	lock_sock(sk);
	if (psock->cork) {
		msg = psock->cork;
	} else {
		msg = &tmp;
		sk_msg_init(msg);
	}

	/* Catch case where ring is full and sendpage is stalled. */
	if (unlikely(sk_msg_full(msg)))
		goto out_err;

	sk_msg_page_add(msg, page, size, offset);
	sk_mem_charge(sk, size);
	copied = size;
	if (sk_msg_full(msg))
		enospc = true;
	if (psock->cork_bytes) {
		if (size > psock->cork_bytes)
			psock->cork_bytes = 0;
		else
			psock->cork_bytes -= size;
		if (psock->cork_bytes && !enospc)
			goto out_err;
		/* All cork bytes are accounted, rerun the prog. */
		psock->eval = __SK_NONE;
		psock->cork_bytes = 0;
	}

	err = tcp_bpf_send_verdict(sk, psock, msg, &copied, flags);
out_err:
	release_sock(sk);
	sk_psock_put(sk, psock);
	return copied ? copied : err;
}