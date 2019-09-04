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
struct rockchip_pcie_ep {TYPE_1__* epc; int /*<<< orphan*/  max_regions; } ;
struct rockchip_pcie {struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {int max_functions; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_REGION_LIMIT ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u8 (int /*<<< orphan*/ ,char*,int*) ; 
 int rockchip_pcie_get_phys (struct rockchip_pcie*) ; 
 int rockchip_pcie_parse_dt (struct rockchip_pcie*) ; 

__attribute__((used)) static int rockchip_pcie_parse_ep_dt(struct rockchip_pcie *rockchip,
				     struct rockchip_pcie_ep *ep)
{
	struct device *dev = rockchip->dev;
	int err;

	err = rockchip_pcie_parse_dt(rockchip);
	if (err)
		return err;

	err = rockchip_pcie_get_phys(rockchip);
	if (err)
		return err;

	err = of_property_read_u32(dev->of_node,
				   "rockchip,max-outbound-regions",
				   &ep->max_regions);
	if (err < 0 || ep->max_regions > MAX_REGION_LIMIT)
		ep->max_regions = MAX_REGION_LIMIT;

	err = of_property_read_u8(dev->of_node, "max-functions",
				  &ep->epc->max_functions);
	if (err < 0)
		ep->epc->max_functions = 1;

	return 0;
}