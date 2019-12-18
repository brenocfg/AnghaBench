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
typedef  int /*<<< orphan*/  u8 ;
struct amp_mgr {int /*<<< orphan*/  amp_ctrls_lock; int /*<<< orphan*/  amp_ctrls; } ;
struct amp_ctrl {int /*<<< orphan*/  list; int /*<<< orphan*/  id; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct amp_mgr*,struct amp_ctrl*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct amp_ctrl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct amp_ctrl *amp_ctrl_add(struct amp_mgr *mgr, u8 id)
{
	struct amp_ctrl *ctrl;

	ctrl = kzalloc(sizeof(*ctrl), GFP_KERNEL);
	if (!ctrl)
		return NULL;

	kref_init(&ctrl->kref);
	ctrl->id = id;

	mutex_lock(&mgr->amp_ctrls_lock);
	list_add(&ctrl->list, &mgr->amp_ctrls);
	mutex_unlock(&mgr->amp_ctrls_lock);

	BT_DBG("mgr %p ctrl %p", mgr, ctrl);

	return ctrl;
}