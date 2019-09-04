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
typedef  int /*<<< orphan*/  tc_setup_cb_t ;
struct tcf_action_egdev_cb {int /*<<< orphan*/  list; } ;
struct tcf_action_egdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct tcf_action_egdev_cb*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct tcf_action_egdev_cb* tcf_action_egdev_cb_lookup (struct tcf_action_egdev*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void tcf_action_egdev_cb_del(struct tcf_action_egdev *egdev,
				    tc_setup_cb_t *cb, void *cb_priv)
{
	struct tcf_action_egdev_cb *egdev_cb;

	egdev_cb = tcf_action_egdev_cb_lookup(egdev, cb, cb_priv);
	if (WARN_ON(!egdev_cb))
		return;
	list_del(&egdev_cb->list);
	kfree(egdev_cb);
}