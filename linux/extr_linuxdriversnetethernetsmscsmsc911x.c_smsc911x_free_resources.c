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
struct smsc911x_data {int /*<<< orphan*/ * clk; int /*<<< orphan*/  supplies; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smsc911x_free_resources(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct smsc911x_data *pdata = netdev_priv(ndev);

	/* Free regulators */
	regulator_bulk_free(ARRAY_SIZE(pdata->supplies),
			pdata->supplies);

	/* Free clock */
	if (!IS_ERR(pdata->clk)) {
		clk_put(pdata->clk);
		pdata->clk = NULL;
	}
}