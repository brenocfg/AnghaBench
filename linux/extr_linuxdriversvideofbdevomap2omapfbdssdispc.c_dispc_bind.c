#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_8__ {scalar_t__ irq; int /*<<< orphan*/  syscon_pol_offset; int /*<<< orphan*/  syscon_pol; struct platform_device* pdev; int /*<<< orphan*/  base; int /*<<< orphan*/  feat; int /*<<< orphan*/  control_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_REVISION ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _omap_dispc_initial_config () ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ dispc ; 
 int /*<<< orphan*/  dispc_dump_regs ; 
 int /*<<< orphan*/  dispc_get_features () ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 
 int dispc_runtime_get () ; 
 int /*<<< orphan*/  dispc_runtime_put () ; 
 int /*<<< orphan*/  dss_debugfs_create_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_init_overlay_managers () ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int dispc_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	u32 rev;
	int r = 0;
	struct resource *dispc_mem;
	struct device_node *np = pdev->dev.of_node;

	dispc.pdev = pdev;

	spin_lock_init(&dispc.control_lock);

	dispc.feat = dispc_get_features();
	if (!dispc.feat)
		return -ENODEV;

	dispc_mem = platform_get_resource(dispc.pdev, IORESOURCE_MEM, 0);
	if (!dispc_mem) {
		DSSERR("can't get IORESOURCE_MEM DISPC\n");
		return -EINVAL;
	}

	dispc.base = devm_ioremap(&pdev->dev, dispc_mem->start,
				  resource_size(dispc_mem));
	if (!dispc.base) {
		DSSERR("can't ioremap DISPC\n");
		return -ENOMEM;
	}

	dispc.irq = platform_get_irq(dispc.pdev, 0);
	if (dispc.irq < 0) {
		DSSERR("platform_get_irq failed\n");
		return -ENODEV;
	}

	if (np && of_property_read_bool(np, "syscon-pol")) {
		dispc.syscon_pol = syscon_regmap_lookup_by_phandle(np, "syscon-pol");
		if (IS_ERR(dispc.syscon_pol)) {
			dev_err(&pdev->dev, "failed to get syscon-pol regmap\n");
			return PTR_ERR(dispc.syscon_pol);
		}

		if (of_property_read_u32_index(np, "syscon-pol", 1,
				&dispc.syscon_pol_offset)) {
			dev_err(&pdev->dev, "failed to get syscon-pol offset\n");
			return -EINVAL;
		}
	}

	pm_runtime_enable(&pdev->dev);

	r = dispc_runtime_get();
	if (r)
		goto err_runtime_get;

	_omap_dispc_initial_config();

	rev = dispc_read_reg(DISPC_REVISION);
	dev_dbg(&pdev->dev, "OMAP DISPC rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dispc_runtime_put();

	dss_init_overlay_managers();

	dss_debugfs_create_file("dispc", dispc_dump_regs);

	return 0;

err_runtime_get:
	pm_runtime_disable(&pdev->dev);
	return r;
}