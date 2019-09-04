#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; TYPE_1__* id_entry; } ;
struct of_device_id {TYPE_1__* data; } ;
struct TYPE_6__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 scalar_t__ IMX31_AUDMUX ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * audmux_base ; 
 int /*<<< orphan*/ * audmux_clk ; 
 int /*<<< orphan*/  audmux_debugfs_init () ; 
 scalar_t__ audmux_type ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  imx_audmux_dt_ids ; 
 int /*<<< orphan*/  imx_audmux_parse_dt_defaults (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_audmux_probe(struct platform_device *pdev)
{
	struct resource *res;
	const struct of_device_id *of_id =
			of_match_device(imx_audmux_dt_ids, &pdev->dev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	audmux_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(audmux_base))
		return PTR_ERR(audmux_base);

	audmux_clk = devm_clk_get(&pdev->dev, "audmux");
	if (IS_ERR(audmux_clk)) {
		dev_dbg(&pdev->dev, "cannot get clock: %ld\n",
				PTR_ERR(audmux_clk));
		audmux_clk = NULL;
	}

	if (of_id)
		pdev->id_entry = of_id->data;
	audmux_type = pdev->id_entry->driver_data;
	if (audmux_type == IMX31_AUDMUX)
		audmux_debugfs_init();

	if (of_id)
		imx_audmux_parse_dt_defaults(pdev, pdev->dev.of_node);

	return 0;
}