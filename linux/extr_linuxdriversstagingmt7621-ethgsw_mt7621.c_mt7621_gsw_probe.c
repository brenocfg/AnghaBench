#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mt7620_gsw {int /*<<< orphan*/  irq; TYPE_1__* dev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mt7620_gsw* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mt7620_gsw*) ; 

__attribute__((used)) static int mt7621_gsw_probe(struct platform_device *pdev)
{
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	struct mt7620_gsw *gsw;

	gsw = devm_kzalloc(&pdev->dev, sizeof(struct mt7620_gsw), GFP_KERNEL);
	if (!gsw)
		return -ENOMEM;

	gsw->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gsw->base))
		return PTR_ERR(gsw->base);

	gsw->dev = &pdev->dev;
	gsw->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);

	platform_set_drvdata(pdev, gsw);

	return 0;
}