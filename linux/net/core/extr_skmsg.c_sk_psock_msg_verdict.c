#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_parser; } ;
struct sk_psock {int /*<<< orphan*/  sk_redir; int /*<<< orphan*/  apply_bytes; TYPE_1__ progs; } ;
struct sk_msg {int /*<<< orphan*/  sk_redir; int /*<<< orphan*/  apply_bytes; struct sock* sk; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int BPF_PROG_RUN (struct bpf_prog*,struct sk_msg*) ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
 int __SK_DROP ; 
 int __SK_PASS ; 
 int __SK_REDIRECT ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_msg_compute_data_pointers (struct sk_msg*) ; 
 int sk_psock_map_verd (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int sk_psock_msg_verdict(struct sock *sk, struct sk_psock *psock,
			 struct sk_msg *msg)
{
	struct bpf_prog *prog;
	int ret;

	preempt_disable();
	rcu_read_lock();
	prog = READ_ONCE(psock->progs.msg_parser);
	if (unlikely(!prog)) {
		ret = __SK_PASS;
		goto out;
	}

	sk_msg_compute_data_pointers(msg);
	msg->sk = sk;
	ret = BPF_PROG_RUN(prog, msg);
	ret = sk_psock_map_verd(ret, msg->sk_redir);
	psock->apply_bytes = msg->apply_bytes;
	if (ret == __SK_REDIRECT) {
		if (psock->sk_redir)
			sock_put(psock->sk_redir);
		psock->sk_redir = msg->sk_redir;
		if (!psock->sk_redir) {
			ret = __SK_DROP;
			goto out;
		}
		sock_hold(psock->sk_redir);
	}
out:
	rcu_read_unlock();
	preempt_enable();
	return ret;
}