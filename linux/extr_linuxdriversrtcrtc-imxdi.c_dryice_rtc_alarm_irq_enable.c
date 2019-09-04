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
struct imxdi_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIER_CAIE ; 
 struct imxdi_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  di_int_disable (struct imxdi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_int_enable (struct imxdi_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dryice_rtc_alarm_irq_enable(struct device *dev,
		unsigned int enabled)
{
	struct imxdi_dev *imxdi = dev_get_drvdata(dev);

	if (enabled)
		di_int_enable(imxdi, DIER_CAIE);
	else
		di_int_disable(imxdi, DIER_CAIE);

	return 0;
}