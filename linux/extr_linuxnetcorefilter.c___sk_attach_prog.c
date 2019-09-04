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
struct sock {int /*<<< orphan*/  sk_filter; } ;
struct sk_filter {int /*<<< orphan*/  refcnt; struct bpf_prog* prog; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __sk_filter_charge (struct sock*,struct sk_filter*) ; 
 int /*<<< orphan*/  kfree (struct sk_filter*) ; 
 struct sk_filter* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_sock_is_held (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sk_filter*) ; 
 struct sk_filter* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_filter_uncharge (struct sock*,struct sk_filter*) ; 

__attribute__((used)) static int __sk_attach_prog(struct bpf_prog *prog, struct sock *sk)
{
	struct sk_filter *fp, *old_fp;

	fp = kmalloc(sizeof(*fp), GFP_KERNEL);
	if (!fp)
		return -ENOMEM;

	fp->prog = prog;

	if (!__sk_filter_charge(sk, fp)) {
		kfree(fp);
		return -ENOMEM;
	}
	refcount_set(&fp->refcnt, 1);

	old_fp = rcu_dereference_protected(sk->sk_filter,
					   lockdep_sock_is_held(sk));
	rcu_assign_pointer(sk->sk_filter, fp);

	if (old_fp)
		sk_filter_uncharge(sk, old_fp);

	return 0;
}