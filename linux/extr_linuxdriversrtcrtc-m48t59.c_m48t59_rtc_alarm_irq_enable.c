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
struct m48t59_private {int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M48T59_INTR ; 
 int M48T59_INTR_AFE ; 
 int /*<<< orphan*/  M48T59_WRITE (int,int /*<<< orphan*/ ) ; 
 struct m48t59_private* dev_get_drvdata (struct device*) ; 
 struct m48t59_plat_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int m48t59_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct m48t59_plat_data *pdata = dev_get_platdata(dev);
	struct m48t59_private *m48t59 = dev_get_drvdata(dev);
	unsigned long flags;

	spin_lock_irqsave(&m48t59->lock, flags);
	if (enabled)
		M48T59_WRITE(M48T59_INTR_AFE, M48T59_INTR);
	else
		M48T59_WRITE(0x00, M48T59_INTR);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	return 0;
}