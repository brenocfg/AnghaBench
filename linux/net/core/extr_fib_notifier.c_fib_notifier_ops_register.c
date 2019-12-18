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
struct net {int dummy; } ;
struct fib_notifier_ops {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fib_notifier_ops* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __fib_notifier_ops_register (struct fib_notifier_ops*,struct net*) ; 
 int /*<<< orphan*/  kfree (struct fib_notifier_ops*) ; 
 struct fib_notifier_ops* kmemdup (struct fib_notifier_ops const*,int,int /*<<< orphan*/ ) ; 

struct fib_notifier_ops *
fib_notifier_ops_register(const struct fib_notifier_ops *tmpl, struct net *net)
{
	struct fib_notifier_ops *ops;
	int err;

	ops = kmemdup(tmpl, sizeof(*ops), GFP_KERNEL);
	if (!ops)
		return ERR_PTR(-ENOMEM);

	err = __fib_notifier_ops_register(ops, net);
	if (err)
		goto err_register;

	return ops;

err_register:
	kfree(ops);
	return ERR_PTR(err);
}