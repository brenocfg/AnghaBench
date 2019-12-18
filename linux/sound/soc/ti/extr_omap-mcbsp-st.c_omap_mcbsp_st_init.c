#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct omap_mcbsp_st_data {int /*<<< orphan*/  io_base_st; int /*<<< orphan*/ * mcbsp_iclk; } ;
struct omap_mcbsp {struct omap_mcbsp_st_data* st_data; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_mcbsp_st_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct omap_mcbsp* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sidetone_attr_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int omap_mcbsp_st_init(struct platform_device *pdev)
{
	struct omap_mcbsp *mcbsp = platform_get_drvdata(pdev);
	struct omap_mcbsp_st_data *st_data;
	struct resource *res;
	int ret;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "sidetone");
	if (!res)
		return 0;

	st_data = devm_kzalloc(mcbsp->dev, sizeof(*mcbsp->st_data), GFP_KERNEL);
	if (!st_data)
		return -ENOMEM;

	st_data->mcbsp_iclk = clk_get(mcbsp->dev, "ick");
	if (IS_ERR(st_data->mcbsp_iclk)) {
		dev_warn(mcbsp->dev,
			 "Failed to get ick, sidetone might be broken\n");
		st_data->mcbsp_iclk = NULL;
	}

	st_data->io_base_st = devm_ioremap(mcbsp->dev, res->start,
					   resource_size(res));
	if (!st_data->io_base_st)
		return -ENOMEM;

	ret = sysfs_create_group(&mcbsp->dev->kobj, &sidetone_attr_group);
	if (ret)
		return ret;

	mcbsp->st_data = st_data;

	return 0;
}