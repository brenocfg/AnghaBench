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
struct platform_device {int dummy; } ;
struct mtk_eth {struct mt7620_gsw* sw_priv; struct device_node* switch_np; } ;
struct mt7620_gsw {int /*<<< orphan*/  irq; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  compatible; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsw_interrupt_mt7621 ; 
 TYPE_1__* mediatek_gsw_match ; 
 int /*<<< orphan*/  mt7621_hw_init (struct mtk_eth*,struct mt7620_gsw*,struct device_node*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,int /*<<< orphan*/ ) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct mt7620_gsw* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mtk_eth*) ; 

int mtk_gsw_init(struct mtk_eth *eth)
{
	struct device_node *np = eth->switch_np;
	struct platform_device *pdev = of_find_device_by_node(np);
	struct mt7620_gsw *gsw;

	if (!pdev)
		return -ENODEV;

	if (!of_device_is_compatible(np, mediatek_gsw_match->compatible))
		return -EINVAL;

	gsw = platform_get_drvdata(pdev);
	eth->sw_priv = gsw;

	if (!gsw->irq)
		return -EINVAL;

	request_irq(gsw->irq, gsw_interrupt_mt7621, 0,
		    "gsw", eth);
	disable_irq(gsw->irq);

	mt7621_hw_init(eth, gsw, np);

	enable_irq(gsw->irq);

	return 0;
}