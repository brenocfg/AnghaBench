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
struct smsc911x_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  reset_gpiod; TYPE_1__* supplies; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int smsc911x_request_resources(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct smsc911x_data *pdata = netdev_priv(ndev);
	int ret = 0;

	/* Request regulators */
	pdata->supplies[0].supply = "vdd33a";
	pdata->supplies[1].supply = "vddvario";
	ret = regulator_bulk_get(&pdev->dev,
			ARRAY_SIZE(pdata->supplies),
			pdata->supplies);
	if (ret) {
		/*
		 * Retry on deferrals, else just report the error
		 * and try to continue.
		 */
		if (ret == -EPROBE_DEFER)
			return ret;
		netdev_err(ndev, "couldn't get regulators %d\n",
				ret);
	}

	/* Request optional RESET GPIO */
	pdata->reset_gpiod = devm_gpiod_get_optional(&pdev->dev,
						     "reset",
						     GPIOD_OUT_LOW);

	/* Request clock */
	pdata->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(pdata->clk))
		dev_dbg(&pdev->dev, "couldn't get clock %li\n",
			PTR_ERR(pdata->clk));

	return ret;
}