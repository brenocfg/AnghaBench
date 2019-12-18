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
struct gsw_mt753x {int /*<<< orphan*/  list; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt753x_devs ; 
 int /*<<< orphan*/  mt753x_devs_lock ; 
 int /*<<< orphan*/  mt753x_id ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt753x_add_gsw(struct gsw_mt753x *gsw)
{
	mutex_lock(&mt753x_devs_lock);
	gsw->id = mt753x_id++;
	INIT_LIST_HEAD(&gsw->list);
	list_add_tail(&gsw->list, &mt753x_devs);
	mutex_unlock(&mt753x_devs_lock);
}