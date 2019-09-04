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
struct pcf85363 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  rtc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_FLAGS ; 
 unsigned int FLAGS_A1F ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 struct pcf85363* i2c_get_clientdata (void*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t pcf85363_rtc_handle_irq(int irq, void *dev_id)
{
	struct pcf85363 *pcf85363 = i2c_get_clientdata(dev_id);
	unsigned int flags;
	int err;

	err = regmap_read(pcf85363->regmap, CTRL_FLAGS, &flags);
	if (err)
		return IRQ_NONE;

	if (flags & FLAGS_A1F) {
		rtc_update_irq(pcf85363->rtc, 1, RTC_IRQF | RTC_AF);
		regmap_update_bits(pcf85363->regmap, CTRL_FLAGS, FLAGS_A1F, 0);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}