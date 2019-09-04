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
struct isp1362_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __isp1362_sw_reset (struct isp1362_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void isp1362_sw_reset(struct isp1362_hcd *isp1362_hcd)
{
	unsigned long flags;

	spin_lock_irqsave(&isp1362_hcd->lock, flags);
	__isp1362_sw_reset(isp1362_hcd);
	spin_unlock_irqrestore(&isp1362_hcd->lock, flags);
}