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
typedef  int u32 ;
struct gemini_powercon {int /*<<< orphan*/  dev; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GEMINI_CTRL_IRQ_CLR ; 
 scalar_t__ GEMINI_PWC_CTRLREG ; 
 scalar_t__ GEMINI_PWC_STATREG ; 
#define  GEMINI_STAT_CIR 130 
#define  GEMINI_STAT_POWERBUTTON 129 
#define  GEMINI_STAT_RTC 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t gemini_powerbutton_interrupt(int irq, void *data)
{
	struct gemini_powercon *gpw = data;
	u32 val;

	/* ACK the IRQ */
	val = readl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_IRQ_CLR;
	writel(val, gpw->base + GEMINI_PWC_CTRLREG);

	val = readl(gpw->base + GEMINI_PWC_STATREG);
	val &= 0x70U;
	switch (val) {
	case GEMINI_STAT_CIR:
		/*
		 * We do not yet have a driver for the infrared
		 * controller so it can cause spurious poweroff
		 * events. Ignore those for now.
		 */
		dev_info(gpw->dev, "infrared poweroff - ignored\n");
		break;
	case GEMINI_STAT_RTC:
		dev_info(gpw->dev, "RTC poweroff\n");
		orderly_poweroff(true);
		break;
	case GEMINI_STAT_POWERBUTTON:
		dev_info(gpw->dev, "poweroff button pressed\n");
		orderly_poweroff(true);
		break;
	default:
		dev_info(gpw->dev, "other power management IRQ\n");
		break;
	}

	return IRQ_HANDLED;
}