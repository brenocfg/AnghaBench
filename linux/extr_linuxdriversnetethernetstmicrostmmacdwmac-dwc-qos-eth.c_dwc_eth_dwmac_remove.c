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
struct stmmac_priv {int /*<<< orphan*/  plat; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct dwc_eth_dwmac_data {int (* remove ) (struct platform_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 struct dwc_eth_dwmac_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int stmmac_dvr_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct platform_device*) ; 

__attribute__((used)) static int dwc_eth_dwmac_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct stmmac_priv *priv = netdev_priv(ndev);
	const struct dwc_eth_dwmac_data *data;
	int err;

	data = of_device_get_match_data(&pdev->dev);

	err = stmmac_dvr_remove(&pdev->dev);
	if (err < 0)
		dev_err(&pdev->dev, "failed to remove platform: %d\n", err);

	err = data->remove(pdev);
	if (err < 0)
		dev_err(&pdev->dev, "failed to remove subdriver: %d\n", err);

	stmmac_remove_config_dt(pdev, priv->plat);

	return err;
}