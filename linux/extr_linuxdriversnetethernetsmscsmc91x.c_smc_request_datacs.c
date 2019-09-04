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
struct smc_local {int /*<<< orphan*/  datacs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDNAME ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ SMC_CAN_USE_DATACS ; 
 int /*<<< orphan*/  SMC_DATA_EXTENT ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct smc_local* netdev_priv (struct net_device*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smc_request_datacs(struct platform_device *pdev, struct net_device *ndev)
{
	if (SMC_CAN_USE_DATACS) {
		struct resource * res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-data32");
		struct smc_local *lp = netdev_priv(ndev);

		if (!res)
			return;

		if(!request_mem_region(res->start, SMC_DATA_EXTENT, CARDNAME)) {
			netdev_info(ndev, "%s: failed to request datacs memory region.\n",
				    CARDNAME);
			return;
		}

		lp->datacs = ioremap(res->start, SMC_DATA_EXTENT);
	}
}