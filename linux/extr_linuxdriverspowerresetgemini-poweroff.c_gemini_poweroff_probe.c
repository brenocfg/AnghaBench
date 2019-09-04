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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gemini_powercon {scalar_t__ base; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GEMINI_CTRL_ENABLE ; 
 int GEMINI_CTRL_IRQ_CLR ; 
 scalar_t__ GEMINI_PWC_CTRLREG ; 
 int GEMINI_PWC_ID ; 
 scalar_t__ GEMINI_PWC_IDREG ; 
 scalar_t__ GEMINI_PWC_STATREG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct gemini_powercon* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gemini_powercon*) ; 
 int /*<<< orphan*/  gemini_powerbutton_interrupt ; 
 int /*<<< orphan*/  gemini_poweroff ; 
 struct gemini_powercon* gpw_poweroff ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_power_off ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int gemini_poweroff_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct gemini_powercon *gpw;
	u32 val;
	int irq;
	int ret;

	gpw = devm_kzalloc(dev, sizeof(*gpw), GFP_KERNEL);
	if (!gpw)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gpw->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(gpw->base))
		return PTR_ERR(gpw->base);

	irq = platform_get_irq(pdev, 0);
	if (!irq)
		return -EINVAL;

	gpw->dev = dev;

	val = readl(gpw->base + GEMINI_PWC_IDREG);
	val &= 0xFFFFFF00U;
	if (val != GEMINI_PWC_ID) {
		dev_err(dev, "wrong power controller ID: %08x\n",
			val);
		return -ENODEV;
	}

	/*
	 * Enable the power controller. This is crucial on Gemini
	 * systems: if this is not done, pressing the power button
	 * will result in unconditional poweroff without any warning.
	 * This makes the kernel handle the poweroff.
	 */
	val = readl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_ENABLE;
	writel(val, gpw->base + GEMINI_PWC_CTRLREG);

	/* Clear the IRQ */
	val = readl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_IRQ_CLR;
	writel(val, gpw->base + GEMINI_PWC_CTRLREG);

	/* Wait for this to clear */
	val = readl(gpw->base + GEMINI_PWC_STATREG);
	while (val & 0x70U)
		val = readl(gpw->base + GEMINI_PWC_STATREG);

	/* Clear the IRQ again */
	val = readl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_IRQ_CLR;
	writel(val, gpw->base + GEMINI_PWC_CTRLREG);

	ret = devm_request_irq(dev, irq, gemini_powerbutton_interrupt, 0,
			       "poweroff", gpw);
	if (ret)
		return ret;

	pm_power_off = gemini_poweroff;
	gpw_poweroff = gpw;

	dev_info(dev, "Gemini poweroff driver registered\n");

	return 0;
}