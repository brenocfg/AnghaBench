#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; TYPE_1__* id_entry; } ;
struct of_device_id {TYPE_1__* data; } ;
struct TYPE_7__ {int driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IMX21_AUDMUX 129 
#define  IMX31_AUDMUX 128 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * audmux_base ; 
 int /*<<< orphan*/ * audmux_clk ; 
 int /*<<< orphan*/  audmux_debugfs_init () ; 
 int audmux_type ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_audmux_dt_ids ; 
 int /*<<< orphan*/  imx_audmux_parse_dt_defaults (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int reg_max ; 
 int /*<<< orphan*/  regcache ; 

__attribute__((used)) static int imx_audmux_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
			of_match_device(imx_audmux_dt_ids, &pdev->dev);

	audmux_base = devm_platform_ioremap_resource(pdev, 0);
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

	switch (audmux_type) {
	case IMX31_AUDMUX:
		audmux_debugfs_init();
		reg_max = 14;
		break;
	case IMX21_AUDMUX:
		reg_max = 6;
		break;
	default:
		dev_err(&pdev->dev, "unsupported version!\n");
		return -EINVAL;
	}

	regcache = devm_kzalloc(&pdev->dev, sizeof(u32) * reg_max, GFP_KERNEL);
	if (!regcache)
		return -ENOMEM;

	if (of_id)
		imx_audmux_parse_dt_defaults(pdev, pdev->dev.of_node);

	return 0;
}