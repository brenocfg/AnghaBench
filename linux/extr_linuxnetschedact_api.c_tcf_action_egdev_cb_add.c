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
struct tcf_action_egdev_cb {int /*<<< orphan*/  list; void* cb_priv; int /*<<< orphan*/ * cb; } ;
struct tcf_action_egdev {int /*<<< orphan*/  cb_list; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (struct tcf_action_egdev_cb*) ; 
 struct tcf_action_egdev_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tcf_action_egdev_cb* tcf_action_egdev_cb_lookup (struct tcf_action_egdev*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int tcf_action_egdev_cb_add(struct tcf_action_egdev *egdev,
				   tc_setup_cb_t *cb, void *cb_priv)
{
	struct tcf_action_egdev_cb *egdev_cb;

	egdev_cb = tcf_action_egdev_cb_lookup(egdev, cb, cb_priv);
	if (WARN_ON(egdev_cb))
		return -EEXIST;
	egdev_cb = kzalloc(sizeof(*egdev_cb), GFP_KERNEL);
	if (!egdev_cb)
		return -ENOMEM;
	egdev_cb->cb = cb;
	egdev_cb->cb_priv = cb_priv;
	list_add(&egdev_cb->list, &egdev->cb_list);
	return 0;
}