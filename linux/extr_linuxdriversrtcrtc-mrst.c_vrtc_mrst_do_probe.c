#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct TYPE_10__ {int irq; struct device* dev; TYPE_1__* rtc; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 unsigned char RTC_24H ; 
 int RTC_AIE ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 unsigned char RTC_DM_BINARY ; 
 int RTC_PIE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,TYPE_2__*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct resource* devm_request_mem_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rtc_allocate_device (struct device*) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  mrst_irq_disable (TYPE_2__*,int) ; 
 TYPE_2__ mrst_rtc ; 
 int /*<<< orphan*/  mrst_rtc_irq ; 
 int /*<<< orphan*/  mrst_rtc_ops ; 
 int /*<<< orphan*/  rename_region (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 unsigned char vrtc_cmos_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vrtc_mrst_do_probe(struct device *dev, struct resource *iomem,
			      int rtc_irq)
{
	int retval = 0;
	unsigned char rtc_control;

	/* There can be only one ... */
	if (mrst_rtc.dev)
		return -EBUSY;

	if (!iomem)
		return -ENODEV;

	iomem = devm_request_mem_region(dev, iomem->start, resource_size(iomem),
					driver_name);
	if (!iomem) {
		dev_dbg(dev, "i/o mem already in use.\n");
		return -EBUSY;
	}

	mrst_rtc.irq = rtc_irq;
	mrst_rtc.dev = dev;
	dev_set_drvdata(dev, &mrst_rtc);

	mrst_rtc.rtc = devm_rtc_allocate_device(dev);
	if (IS_ERR(mrst_rtc.rtc))
		return PTR_ERR(mrst_rtc.rtc);

	mrst_rtc.rtc->ops = &mrst_rtc_ops;

	rename_region(iomem, dev_name(&mrst_rtc.rtc->dev));

	spin_lock_irq(&rtc_lock);
	mrst_irq_disable(&mrst_rtc, RTC_PIE | RTC_AIE);
	rtc_control = vrtc_cmos_read(RTC_CONTROL);
	spin_unlock_irq(&rtc_lock);

	if (!(rtc_control & RTC_24H) || (rtc_control & (RTC_DM_BINARY)))
		dev_dbg(dev, "TODO: support more than 24-hr BCD mode\n");

	if (rtc_irq) {
		retval = devm_request_irq(dev, rtc_irq, mrst_rtc_irq,
					  0, dev_name(&mrst_rtc.rtc->dev),
					  mrst_rtc.rtc);
		if (retval < 0) {
			dev_dbg(dev, "IRQ %d is already in use, err %d\n",
				rtc_irq, retval);
			goto cleanup0;
		}
	}

	retval = rtc_register_device(mrst_rtc.rtc);
	if (retval)
		goto cleanup0;

	dev_dbg(dev, "initialised\n");
	return 0;

cleanup0:
	mrst_rtc.dev = NULL;
	dev_err(dev, "rtc-mrst: unable to initialise\n");
	return retval;
}