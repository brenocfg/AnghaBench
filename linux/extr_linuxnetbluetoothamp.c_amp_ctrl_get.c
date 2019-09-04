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
struct amp_ctrl {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct amp_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 

void amp_ctrl_get(struct amp_ctrl *ctrl)
{
	BT_DBG("ctrl %p orig refcnt %d", ctrl,
	       kref_read(&ctrl->kref));

	kref_get(&ctrl->kref);
}