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
struct net {int dummy; } ;
struct mr_table_ops {int /*<<< orphan*/  rht_params; } ;
struct mr_table {int mroute_reg_vif_num; int /*<<< orphan*/  ipmr_expire_timer; int /*<<< orphan*/  mfc_unres_queue; int /*<<< orphan*/  mfc_cache_list; struct mr_table_ops ops; int /*<<< orphan*/  mfc_hash; int /*<<< orphan*/  net; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mr_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mr_table*) ; 
 struct mr_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int rhltable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,void (*) (struct timer_list*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 

struct mr_table *
mr_table_alloc(struct net *net, u32 id,
	       struct mr_table_ops *ops,
	       void (*expire_func)(struct timer_list *t),
	       void (*table_set)(struct mr_table *mrt,
				 struct net *net))
{
	struct mr_table *mrt;
	int err;

	mrt = kzalloc(sizeof(*mrt), GFP_KERNEL);
	if (!mrt)
		return ERR_PTR(-ENOMEM);
	mrt->id = id;
	write_pnet(&mrt->net, net);

	mrt->ops = *ops;
	err = rhltable_init(&mrt->mfc_hash, mrt->ops.rht_params);
	if (err) {
		kfree(mrt);
		return ERR_PTR(err);
	}
	INIT_LIST_HEAD(&mrt->mfc_cache_list);
	INIT_LIST_HEAD(&mrt->mfc_unres_queue);

	timer_setup(&mrt->ipmr_expire_timer, expire_func, 0);

	mrt->mroute_reg_vif_num = -1;
	table_set(mrt, net);
	return mrt;
}