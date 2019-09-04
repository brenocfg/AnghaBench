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
typedef  int /*<<< orphan*/  u32 ;
struct vme_bridge {int /*<<< orphan*/  parent; struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_EDPAL ; 
 scalar_t__ TSI148_LCSR_EDPAT ; 
 int /*<<< orphan*/  TSI148_LCSR_EDPAT_EDPCL ; 
 scalar_t__ TSI148_LCSR_EDPAU ; 
 scalar_t__ TSI148_LCSR_EDPXA ; 
 scalar_t__ TSI148_LCSR_EDPXS ; 
 int /*<<< orphan*/  TSI148_LCSR_INTC_PERRC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 tsi148_PERR_irqhandler(struct vme_bridge *tsi148_bridge)
{
	struct tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	dev_err(tsi148_bridge->parent, "PCI Exception at address: 0x%08x:%08x, "
		"attributes: %08x\n",
		ioread32be(bridge->base + TSI148_LCSR_EDPAU),
		ioread32be(bridge->base + TSI148_LCSR_EDPAL),
		ioread32be(bridge->base + TSI148_LCSR_EDPAT));

	dev_err(tsi148_bridge->parent, "PCI-X attribute reg: %08x, PCI-X split "
		"completion reg: %08x\n",
		ioread32be(bridge->base + TSI148_LCSR_EDPXA),
		ioread32be(bridge->base + TSI148_LCSR_EDPXS));

	iowrite32be(TSI148_LCSR_EDPAT_EDPCL, bridge->base + TSI148_LCSR_EDPAT);

	return TSI148_LCSR_INTC_PERRC;
}