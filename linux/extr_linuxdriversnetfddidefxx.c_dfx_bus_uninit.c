#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {unsigned long base_addr; } ;
struct TYPE_5__ {struct device* bus_dev; } ;
typedef  TYPE_1__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_printk (char*) ; 
 int DFX_BUS_EISA (struct device*) ; 
 int /*<<< orphan*/  PFI_K_REG_MODE_CTRL ; 
 int /*<<< orphan*/  PI_CONFIG_STAT_0_M_INT_ENB ; 
 scalar_t__ PI_ESIC_K_FUNCTION_CNTRL ; 
 scalar_t__ PI_ESIC_K_IO_CONFIG_STAT_0 ; 
 scalar_t__ PI_ESIC_K_SLOT_CNTRL ; 
 int dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* to_eisa_device (struct device*) ; 

__attribute__((used)) static void dfx_bus_uninit(struct net_device *dev)
{
	DFX_board_t *bp = netdev_priv(dev);
	struct device *bdev = bp->bus_dev;
	int dfx_bus_pci = dev_is_pci(bdev);
	int dfx_bus_eisa = DFX_BUS_EISA(bdev);
	u8 val;

	DBG_printk("In dfx_bus_uninit...\n");

	/* Uninitialize adapter based on bus type */

	if (dfx_bus_eisa) {
		unsigned long base_addr = to_eisa_device(bdev)->base_addr;

		/* Disable interrupts at EISA bus interface chip (ESIC) */
		val = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		val &= ~PI_CONFIG_STAT_0_M_INT_ENB;
		outb(val, base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);

		/* Disable the board.  */
		outb(0, base_addr + PI_ESIC_K_SLOT_CNTRL);

		/* Disable memory and port decoders.  */
		outb(0, base_addr + PI_ESIC_K_FUNCTION_CNTRL);
	}
	if (dfx_bus_pci) {
		/* Disable interrupts at PCI bus interface chip (PFI) */
		dfx_port_write_long(bp, PFI_K_REG_MODE_CTRL, 0);
	}
}