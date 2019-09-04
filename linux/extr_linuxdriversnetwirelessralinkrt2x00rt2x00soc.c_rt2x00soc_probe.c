#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt2x00_ops {int /*<<< orphan*/  hw; } ;
struct rt2x00_dev {int /*<<< orphan*/ * clk; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; struct ieee80211_hw* hw; struct rt2x00_ops const* ops; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct platform_device {TYPE_2__ dev; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT2X00_CHIP_INTF_SOC ; 
 int /*<<< orphan*/ * clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rt2x00_probe_err (char*) ; 
 int /*<<< orphan*/  rt2x00_set_chip_intf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int rt2x00lib_probe_dev (struct rt2x00_dev*) ; 
 int rt2x00soc_alloc_reg (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00soc_free_reg (struct rt2x00_dev*) ; 

int rt2x00soc_probe(struct platform_device *pdev, const struct rt2x00_ops *ops)
{
	struct ieee80211_hw *hw;
	struct rt2x00_dev *rt2x00dev;
	int retval;

	hw = ieee80211_alloc_hw(sizeof(struct rt2x00_dev), ops->hw);
	if (!hw) {
		rt2x00_probe_err("Failed to allocate hardware\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, hw);

	rt2x00dev = hw->priv;
	rt2x00dev->dev = &pdev->dev;
	rt2x00dev->ops = ops;
	rt2x00dev->hw = hw;
	rt2x00dev->irq = platform_get_irq(pdev, 0);
	rt2x00dev->name = pdev->dev.driver->name;

	rt2x00dev->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(rt2x00dev->clk))
		rt2x00dev->clk = NULL;

	rt2x00_set_chip_intf(rt2x00dev, RT2X00_CHIP_INTF_SOC);

	retval = rt2x00soc_alloc_reg(rt2x00dev);
	if (retval)
		goto exit_free_device;

	retval = rt2x00lib_probe_dev(rt2x00dev);
	if (retval)
		goto exit_free_reg;

	return 0;

exit_free_reg:
	rt2x00soc_free_reg(rt2x00dev);

exit_free_device:
	ieee80211_free_hw(hw);

	return retval;
}