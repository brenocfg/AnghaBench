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
struct timer_list {int dummy; } ;
struct mr_table {int /*<<< orphan*/  mfc_unres_queue; int /*<<< orphan*/  ipmr_expire_timer; } ;

/* Variables and functions */
 struct mr_table* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmr_do_expire_process (struct mr_table*) ; 
 int /*<<< orphan*/  ipmr_expire_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfc_unres_lock ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct mr_table* mrt ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmr_expire_process(struct timer_list *t)
{
	struct mr_table *mrt = from_timer(mrt, t, ipmr_expire_timer);

	if (!spin_trylock(&mfc_unres_lock)) {
		mod_timer(&mrt->ipmr_expire_timer, jiffies + 1);
		return;
	}

	if (!list_empty(&mrt->mfc_unres_queue))
		ipmr_do_expire_process(mrt);

	spin_unlock(&mfc_unres_lock);
}