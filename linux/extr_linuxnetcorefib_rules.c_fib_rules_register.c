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
struct fib_rules_ops {struct net* fro_net; int /*<<< orphan*/  rules_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fib_rules_ops* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __fib_rules_register (struct fib_rules_ops*) ; 
 int /*<<< orphan*/  kfree (struct fib_rules_ops*) ; 
 struct fib_rules_ops* kmemdup (struct fib_rules_ops const*,int,int /*<<< orphan*/ ) ; 

struct fib_rules_ops *
fib_rules_register(const struct fib_rules_ops *tmpl, struct net *net)
{
	struct fib_rules_ops *ops;
	int err;

	ops = kmemdup(tmpl, sizeof(*ops), GFP_KERNEL);
	if (ops == NULL)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&ops->rules_list);
	ops->fro_net = net;

	err = __fib_rules_register(ops);
	if (err) {
		kfree(ops);
		ops = ERR_PTR(err);
	}

	return ops;
}