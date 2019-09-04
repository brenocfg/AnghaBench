#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct xlnx_rtc_dev {scalar_t__ alarm_irq; scalar_t__ sec_irq; int /*<<< orphan*/  rtc; int /*<<< orphan*/  calibval; int /*<<< orphan*/  reg_base; } ;
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CALIB_DEF ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct xlnx_rtc_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xlnx_rtc_dev*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xlnx_rtc_dev*) ; 
 int /*<<< orphan*/  xlnx_init_rtc (struct xlnx_rtc_dev*) ; 
 int /*<<< orphan*/  xlnx_rtc_interrupt ; 
 int /*<<< orphan*/  xlnx_rtc_ops ; 

__attribute__((used)) static int xlnx_rtc_probe(struct platform_device *pdev)
{
	struct xlnx_rtc_dev *xrtcdev;
	struct resource *res;
	int ret;

	xrtcdev = devm_kzalloc(&pdev->dev, sizeof(*xrtcdev), GFP_KERNEL);
	if (!xrtcdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, xrtcdev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	xrtcdev->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xrtcdev->reg_base))
		return PTR_ERR(xrtcdev->reg_base);

	xrtcdev->alarm_irq = platform_get_irq_byname(pdev, "alarm");
	if (xrtcdev->alarm_irq < 0) {
		dev_err(&pdev->dev, "no irq resource\n");
		return xrtcdev->alarm_irq;
	}
	ret = devm_request_irq(&pdev->dev, xrtcdev->alarm_irq,
			       xlnx_rtc_interrupt, 0,
			       dev_name(&pdev->dev), xrtcdev);
	if (ret) {
		dev_err(&pdev->dev, "request irq failed\n");
		return ret;
	}

	xrtcdev->sec_irq = platform_get_irq_byname(pdev, "sec");
	if (xrtcdev->sec_irq < 0) {
		dev_err(&pdev->dev, "no irq resource\n");
		return xrtcdev->sec_irq;
	}
	ret = devm_request_irq(&pdev->dev, xrtcdev->sec_irq,
			       xlnx_rtc_interrupt, 0,
			       dev_name(&pdev->dev), xrtcdev);
	if (ret) {
		dev_err(&pdev->dev, "request irq failed\n");
		return ret;
	}

	ret = of_property_read_u32(pdev->dev.of_node, "calibration",
				   &xrtcdev->calibval);
	if (ret)
		xrtcdev->calibval = RTC_CALIB_DEF;

	xlnx_init_rtc(xrtcdev);

	device_init_wakeup(&pdev->dev, 1);

	xrtcdev->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
					 &xlnx_rtc_ops, THIS_MODULE);
	return PTR_ERR_OR_ZERO(xrtcdev->rtc);
}