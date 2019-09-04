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
struct zfcp_adapter {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_adapter_release ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_ref_lock ; 

void zfcp_ccw_adapter_put(struct zfcp_adapter *adapter)
{
	unsigned long flags;

	spin_lock_irqsave(&zfcp_ccw_adapter_ref_lock, flags);
	kref_put(&adapter->ref, zfcp_adapter_release);
	spin_unlock_irqrestore(&zfcp_ccw_adapter_ref_lock, flags);
}