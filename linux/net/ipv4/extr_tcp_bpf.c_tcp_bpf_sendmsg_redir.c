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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_psock {int dummy; } ;
struct sk_msg {int dummy; } ;

/* Variables and functions */
 int bpf_tcp_ingress (struct sock*,struct sk_psock*,struct sk_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_msg_free (struct sock*,struct sk_msg*) ; 
 int sk_msg_to_ingress (struct sk_msg*) ; 
 struct sk_psock* sk_psock_get (struct sock*) ; 
 int /*<<< orphan*/  sk_psock_put (struct sock*,struct sk_psock*) ; 
 int tcp_bpf_push_locked (struct sock*,struct sk_msg*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 

int tcp_bpf_sendmsg_redir(struct sock *sk, struct sk_msg *msg,
			  u32 bytes, int flags)
{
	bool ingress = sk_msg_to_ingress(msg);
	struct sk_psock *psock = sk_psock_get(sk);
	int ret;

	if (unlikely(!psock)) {
		sk_msg_free(sk, msg);
		return 0;
	}
	ret = ingress ? bpf_tcp_ingress(sk, psock, msg, bytes, flags) :
			tcp_bpf_push_locked(sk, msg, bytes, flags, false);
	sk_psock_put(sk, psock);
	return ret;
}