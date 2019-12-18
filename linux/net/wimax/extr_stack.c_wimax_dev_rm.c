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
struct wimax_dev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIMAX_ST_DOWN ; 
 int /*<<< orphan*/  __WIMAX_ST_QUIESCING ; 
 int /*<<< orphan*/  __wimax_state_change (struct wimax_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_fnend (int,int /*<<< orphan*/ *,char*,struct wimax_dev*) ; 
 int /*<<< orphan*/  d_fnstart (int,int /*<<< orphan*/ *,char*,struct wimax_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wimax_debugfs_rm (struct wimax_dev*) ; 
 int /*<<< orphan*/  wimax_id_table_rm (struct wimax_dev*) ; 
 int /*<<< orphan*/  wimax_rfkill_rm (struct wimax_dev*) ; 

void wimax_dev_rm(struct wimax_dev *wimax_dev)
{
	d_fnstart(3, NULL, "(wimax_dev %p)\n", wimax_dev);

	mutex_lock(&wimax_dev->mutex);
	__wimax_state_change(wimax_dev, __WIMAX_ST_QUIESCING);
	wimax_debugfs_rm(wimax_dev);
	wimax_id_table_rm(wimax_dev);
	__wimax_state_change(wimax_dev, WIMAX_ST_DOWN);
	mutex_unlock(&wimax_dev->mutex);
	wimax_rfkill_rm(wimax_dev);
	d_fnend(3, NULL, "(wimax_dev %p) = void\n", wimax_dev);
}