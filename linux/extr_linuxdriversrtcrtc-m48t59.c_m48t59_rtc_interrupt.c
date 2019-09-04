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
typedef  int u8 ;
struct m48t59_private {int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  M48T59_FLAGS ; 
 int M48T59_FLAGS_AF ; 
 int M48T59_READ (int /*<<< orphan*/ ) ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 struct m48t59_private* dev_get_drvdata (struct device*) ; 
 struct m48t59_plat_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t m48t59_rtc_interrupt(int irq, void *dev_id)
{
	struct device *dev = (struct device *)dev_id;
	struct m48t59_plat_data *pdata = dev_get_platdata(dev);
	struct m48t59_private *m48t59 = dev_get_drvdata(dev);
	u8 event;

	spin_lock(&m48t59->lock);
	event = M48T59_READ(M48T59_FLAGS);
	spin_unlock(&m48t59->lock);

	if (event & M48T59_FLAGS_AF) {
		rtc_update_irq(m48t59->rtc, 1, (RTC_AF | RTC_IRQF));
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}