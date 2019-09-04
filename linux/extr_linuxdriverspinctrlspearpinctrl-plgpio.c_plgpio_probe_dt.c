#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_5__ {int enb; int eit; void* mis; void* rdata; void* ie; void* dir; void* wdata; } ;
struct TYPE_4__ {void* ngpio; } ;
struct plgpio {int p2o_regs; TYPE_2__ regs; TYPE_1__ chip; int /*<<< orphan*/  o2p; int /*<<< orphan*/  p2o; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTO_DIR_REG ; 
 int PTO_IE_REG ; 
 int PTO_MIS_REG ; 
 int PTO_RDATA_REG ; 
 int PTO_WDATA_REG ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,void**) ; 
 int /*<<< orphan*/  spear310_o2p ; 
 int /*<<< orphan*/  spear310_p2o ; 

__attribute__((used)) static int plgpio_probe_dt(struct platform_device *pdev, struct plgpio *plgpio)
{
	struct device_node *np = pdev->dev.of_node;
	int ret = -EINVAL;
	u32 val;

	if (of_machine_is_compatible("st,spear310")) {
		plgpio->p2o = spear310_p2o;
		plgpio->o2p = spear310_o2p;
		plgpio->p2o_regs = PTO_WDATA_REG | PTO_DIR_REG | PTO_IE_REG |
			PTO_RDATA_REG | PTO_MIS_REG;
	}

	if (!of_property_read_u32(np, "st-plgpio,ngpio", &val)) {
		plgpio->chip.ngpio = val;
	} else {
		dev_err(&pdev->dev, "DT: Invalid ngpio field\n");
		goto end;
	}

	if (!of_property_read_u32(np, "st-plgpio,enb-reg", &val))
		plgpio->regs.enb = val;
	else
		plgpio->regs.enb = -1;

	if (!of_property_read_u32(np, "st-plgpio,wdata-reg", &val)) {
		plgpio->regs.wdata = val;
	} else {
		dev_err(&pdev->dev, "DT: Invalid wdata reg\n");
		goto end;
	}

	if (!of_property_read_u32(np, "st-plgpio,dir-reg", &val)) {
		plgpio->regs.dir = val;
	} else {
		dev_err(&pdev->dev, "DT: Invalid dir reg\n");
		goto end;
	}

	if (!of_property_read_u32(np, "st-plgpio,ie-reg", &val)) {
		plgpio->regs.ie = val;
	} else {
		dev_err(&pdev->dev, "DT: Invalid ie reg\n");
		goto end;
	}

	if (!of_property_read_u32(np, "st-plgpio,rdata-reg", &val)) {
		plgpio->regs.rdata = val;
	} else {
		dev_err(&pdev->dev, "DT: Invalid rdata reg\n");
		goto end;
	}

	if (!of_property_read_u32(np, "st-plgpio,mis-reg", &val)) {
		plgpio->regs.mis = val;
	} else {
		dev_err(&pdev->dev, "DT: Invalid mis reg\n");
		goto end;
	}

	if (!of_property_read_u32(np, "st-plgpio,eit-reg", &val))
		plgpio->regs.eit = val;
	else
		plgpio->regs.eit = -1;

	return 0;

end:
	return ret;
}