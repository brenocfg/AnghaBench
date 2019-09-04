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
struct pqi_ctrl_info {int /*<<< orphan*/  raid_bypass_retry_list_lock; int /*<<< orphan*/  raid_bypass_retry_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pqi_clear_all_queued_raid_bypass_retries(
	struct pqi_ctrl_info *ctrl_info)
{
	unsigned long flags;

	spin_lock_irqsave(&ctrl_info->raid_bypass_retry_list_lock, flags);
	INIT_LIST_HEAD(&ctrl_info->raid_bypass_retry_list);
	spin_unlock_irqrestore(&ctrl_info->raid_bypass_retry_list_lock, flags);
}