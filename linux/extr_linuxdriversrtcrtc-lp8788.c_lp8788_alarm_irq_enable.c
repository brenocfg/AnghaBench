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
typedef  unsigned int u8 ;
struct lp8788_rtc {size_t alarm; int /*<<< orphan*/  irq; struct lp8788* lp; } ;
struct lp8788 {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LP8788_INTEN_3 ; 
 struct lp8788_rtc* dev_get_drvdata (struct device*) ; 
 int lp8788_update_bits (struct lp8788*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int* mask_alarm_en ; 
 unsigned int* shift_alarm_en ; 

__attribute__((used)) static int lp8788_alarm_irq_enable(struct device *dev, unsigned int enable)
{
	struct lp8788_rtc *rtc = dev_get_drvdata(dev);
	struct lp8788 *lp = rtc->lp;
	u8 mask, shift;

	if (!rtc->irq)
		return -EIO;

	mask = mask_alarm_en[rtc->alarm];
	shift = shift_alarm_en[rtc->alarm];

	return lp8788_update_bits(lp, LP8788_INTEN_3, mask, enable << shift);
}