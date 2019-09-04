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
struct iscsi_tiqn {scalar_t__ tiqn_access_count; int /*<<< orphan*/  tiqn_state_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsit_wait_for_tiqn(struct iscsi_tiqn *tiqn)
{
	/*
	 * Wait for accesses to said struct iscsi_tiqn to end.
	 */
	spin_lock(&tiqn->tiqn_state_lock);
	while (tiqn->tiqn_access_count != 0) {
		spin_unlock(&tiqn->tiqn_state_lock);
		msleep(10);
		spin_lock(&tiqn->tiqn_state_lock);
	}
	spin_unlock(&tiqn->tiqn_state_lock);
}