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
struct platform_device {int dummy; } ;
struct mtk_eth {int /*<<< orphan*/  rx_napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_cleanup (struct mtk_eth*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 struct mtk_eth* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_remove(struct platform_device *pdev)
{
	struct mtk_eth *eth = platform_get_drvdata(pdev);

	netif_napi_del(&eth->rx_napi);
	mtk_cleanup(eth);
	platform_set_drvdata(pdev, NULL);

	return 0;
}