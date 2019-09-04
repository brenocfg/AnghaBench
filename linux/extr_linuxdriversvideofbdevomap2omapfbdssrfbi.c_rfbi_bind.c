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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int l4_khz; int /*<<< orphan*/  base; struct platform_device* pdev; int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  RFBI_REVISION ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 TYPE_1__ rfbi ; 
 int /*<<< orphan*/  rfbi_dump_regs ; 
 int /*<<< orphan*/  rfbi_init_output (struct platform_device*) ; 
 int /*<<< orphan*/  rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int rfbi_runtime_get () ; 
 int /*<<< orphan*/  rfbi_runtime_put () ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int rfbi_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	u32 rev;
	struct resource *rfbi_mem;
	struct clk *clk;
	int r;

	rfbi.pdev = pdev;

	sema_init(&rfbi.bus_lock, 1);

	rfbi_mem = platform_get_resource(rfbi.pdev, IORESOURCE_MEM, 0);
	if (!rfbi_mem) {
		DSSERR("can't get IORESOURCE_MEM RFBI\n");
		return -EINVAL;
	}

	rfbi.base = devm_ioremap(&pdev->dev, rfbi_mem->start,
				 resource_size(rfbi_mem));
	if (!rfbi.base) {
		DSSERR("can't ioremap RFBI\n");
		return -ENOMEM;
	}

	clk = clk_get(&pdev->dev, "ick");
	if (IS_ERR(clk)) {
		DSSERR("can't get ick\n");
		return PTR_ERR(clk);
	}

	rfbi.l4_khz = clk_get_rate(clk) / 1000;

	clk_put(clk);

	pm_runtime_enable(&pdev->dev);

	r = rfbi_runtime_get();
	if (r)
		goto err_runtime_get;

	msleep(10);

	rev = rfbi_read_reg(RFBI_REVISION);
	dev_dbg(&pdev->dev, "OMAP RFBI rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	rfbi_runtime_put();

	dss_debugfs_create_file("rfbi", rfbi_dump_regs);

	rfbi_init_output(pdev);

	return 0;

err_runtime_get:
	pm_runtime_disable(&pdev->dev);
	return r;
}