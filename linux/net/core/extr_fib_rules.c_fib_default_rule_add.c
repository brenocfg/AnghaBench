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
typedef  void* u32 ;
struct fib_rules_ops {int /*<<< orphan*/  rules_list; int /*<<< orphan*/  fro_net; int /*<<< orphan*/  rule_size; } ;
struct fib_rule {int suppress_prefixlen; int suppress_ifgroup; int /*<<< orphan*/  list; int /*<<< orphan*/  uid_range; int /*<<< orphan*/  fr_net; int /*<<< orphan*/  proto; void* flags; void* table; void* pref; int /*<<< orphan*/  action; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FR_ACT_TO_TBL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTPROT_KERNEL ; 
 int /*<<< orphan*/  fib_kuid_range_unset ; 
 struct fib_rule* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

int fib_default_rule_add(struct fib_rules_ops *ops,
			 u32 pref, u32 table, u32 flags)
{
	struct fib_rule *r;

	r = kzalloc(ops->rule_size, GFP_KERNEL);
	if (r == NULL)
		return -ENOMEM;

	refcount_set(&r->refcnt, 1);
	r->action = FR_ACT_TO_TBL;
	r->pref = pref;
	r->table = table;
	r->flags = flags;
	r->proto = RTPROT_KERNEL;
	r->fr_net = ops->fro_net;
	r->uid_range = fib_kuid_range_unset;

	r->suppress_prefixlen = -1;
	r->suppress_ifgroup = -1;

	/* The lock is not required here, the list in unreacheable
	 * at the moment this function is called */
	list_add_tail(&r->list, &ops->rules_list);
	return 0;
}