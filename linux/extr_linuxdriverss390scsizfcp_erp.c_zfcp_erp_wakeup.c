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
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; int /*<<< orphan*/  erp_done_wqh; int /*<<< orphan*/  status; int /*<<< orphan*/  erp_running_head; int /*<<< orphan*/  erp_ready_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_ADAPTER_ERP_PENDING ; 
 int /*<<< orphan*/  atomic_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_erp_wakeup(struct zfcp_adapter *adapter)
{
	unsigned long flags;

	read_lock_irqsave(&adapter->erp_lock, flags);
	if (list_empty(&adapter->erp_ready_head) &&
	    list_empty(&adapter->erp_running_head)) {
			atomic_andnot(ZFCP_STATUS_ADAPTER_ERP_PENDING,
					  &adapter->status);
			wake_up(&adapter->erp_done_wqh);
	}
	read_unlock_irqrestore(&adapter->erp_lock, flags);
}