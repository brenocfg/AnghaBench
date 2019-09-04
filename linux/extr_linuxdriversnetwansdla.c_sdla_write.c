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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sdla_write (struct net_device*,int,void const*,short) ; 
 int /*<<< orphan*/  sdla_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdla_write(struct net_device *dev, int addr, 
		       const void *buf, short len)
{
	unsigned long flags;

	spin_lock_irqsave(&sdla_lock, flags);
	__sdla_write(dev, addr, buf, len);
	spin_unlock_irqrestore(&sdla_lock, flags);
}