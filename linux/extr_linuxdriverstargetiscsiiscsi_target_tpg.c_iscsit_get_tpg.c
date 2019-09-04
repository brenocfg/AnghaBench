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
struct iscsi_portal_group {int /*<<< orphan*/  tpg_access_lock; } ;

/* Variables and functions */
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 

int iscsit_get_tpg(
	struct iscsi_portal_group *tpg)
{
	return mutex_lock_interruptible(&tpg->tpg_access_lock);
}