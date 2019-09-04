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
struct platform_device {int dummy; } ;
struct at91_udc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct at91_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pullup (struct at91_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void at91udc_shutdown(struct platform_device *dev)
{
	struct at91_udc *udc = platform_get_drvdata(dev);
	unsigned long	flags;

	/* force disconnect on reboot */
	spin_lock_irqsave(&udc->lock, flags);
	pullup(platform_get_drvdata(dev), 0);
	spin_unlock_irqrestore(&udc->lock, flags);
}