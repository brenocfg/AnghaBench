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
struct smap_psock {size_t cork_bytes; size_t sg_size; int /*<<< orphan*/  eval; struct sk_msg_buff* cork; int /*<<< orphan*/  refcnt; } ;
struct sk_msg_buff {size_t sg_end; size_t sg_start; int* sg_copy; struct scatterlist* sg_data; int /*<<< orphan*/  member_0; } ;
struct scatterlist {scalar_t__ length; } ;
struct page {int dummy; } ;

/* Variables and functions */
 size_t MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  __SK_NONE ; 
 int bpf_exec_tx_verdict (struct smap_psock*,struct sk_msg_buff*,struct sock*,int*,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sg_init_marker (struct scatterlist*,size_t) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,size_t,int) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,size_t) ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 int /*<<< orphan*/  smap_release_sock (struct smap_psock*,struct sock*) ; 
 int tcp_sendpage (struct sock*,struct page*,int,size_t,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_tcp_sendpage(struct sock *sk, struct page *page,
			    int offset, size_t size, int flags)
{
	struct sk_msg_buff md = {0}, *m = NULL;
	int err = 0, copied = 0;
	struct smap_psock *psock;
	struct scatterlist *sg;
	bool enospc = false;

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (unlikely(!psock))
		goto accept;

	if (!refcount_inc_not_zero(&psock->refcnt))
		goto accept;
	rcu_read_unlock();

	lock_sock(sk);

	if (psock->cork_bytes) {
		m = psock->cork;
		sg = &m->sg_data[m->sg_end];
	} else {
		m = &md;
		sg = m->sg_data;
		sg_init_marker(sg, MAX_SKB_FRAGS);
	}

	/* Catch case where ring is full and sendpage is stalled. */
	if (unlikely(m->sg_end == m->sg_start &&
	    m->sg_data[m->sg_end].length))
		goto out_err;

	psock->sg_size += size;
	sg_set_page(sg, page, size, offset);
	get_page(page);
	m->sg_copy[m->sg_end] = true;
	sk_mem_charge(sk, size);
	m->sg_end++;
	copied = size;

	if (m->sg_end == MAX_SKB_FRAGS)
		m->sg_end = 0;

	if (m->sg_end == m->sg_start)
		enospc = true;

	if (psock->cork_bytes) {
		if (size > psock->cork_bytes)
			psock->cork_bytes = 0;
		else
			psock->cork_bytes -= size;

		if (psock->cork_bytes && !enospc)
			goto out_err;

		/* All cork bytes accounted for re-run filter */
		psock->eval = __SK_NONE;
		psock->cork_bytes = 0;
	}

	err = bpf_exec_tx_verdict(psock, m, sk, &copied, flags);
out_err:
	release_sock(sk);
	smap_release_sock(psock, sk);
	return copied ? copied : err;
accept:
	rcu_read_unlock();
	return tcp_sendpage(sk, page, offset, size, flags);
}