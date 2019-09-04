#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irq_1hz; int /*<<< orphan*/  irq_alarm; } ;
struct pxa_rtc {TYPE_1__ sa1100_rtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  pxa_rtc_irq ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device*) ; 

__attribute__((used)) static int pxa_rtc_open(struct device *dev)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	int ret;

	ret = request_irq(pxa_rtc->sa1100_rtc.irq_1hz, pxa_rtc_irq, 0,
			  "rtc 1Hz", dev);
	if (ret < 0) {
		dev_err(dev, "can't get irq %i, err %d\n",
			pxa_rtc->sa1100_rtc.irq_1hz, ret);
		goto err_irq_1Hz;
	}
	ret = request_irq(pxa_rtc->sa1100_rtc.irq_alarm, pxa_rtc_irq, 0,
			  "rtc Alrm", dev);
	if (ret < 0) {
		dev_err(dev, "can't get irq %i, err %d\n",
			pxa_rtc->sa1100_rtc.irq_alarm, ret);
		goto err_irq_Alrm;
	}

	return 0;

err_irq_Alrm:
	free_irq(pxa_rtc->sa1100_rtc.irq_1hz, dev);
err_irq_1Hz:
	return ret;
}