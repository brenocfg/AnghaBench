#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {unsigned long base_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; struct device* bus_dev; } ;
typedef  TYPE_1__ DFX_board_t ;

/* Variables and functions */
 int DFX_BUS_EISA (struct device*) ; 
 int DFX_BUS_TC (struct device*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PFI_K_REG_MODE_CTRL ; 
 int /*<<< orphan*/  PFI_K_REG_STATUS ; 
 int PFI_MODE_M_DMA_ENB ; 
 int PFI_MODE_M_PDQ_INT_ENB ; 
 int PFI_STATUS_M_PDQ_INT ; 
 int PI_CONFIG_STAT_0_M_INT_ENB ; 
 int PI_CONFIG_STAT_0_M_PEND ; 
 scalar_t__ PI_ESIC_K_IO_CONFIG_STAT_0 ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_STATUS ; 
 int PI_PSTATUS_M_CMD_REQ_PENDING ; 
 int PI_PSTATUS_M_CMD_RSP_PENDING ; 
 int PI_PSTATUS_M_RCV_DATA_PENDING ; 
 int PI_PSTATUS_M_SMT_HOST_PENDING ; 
 int PI_PSTATUS_M_TYPE_0_PENDING ; 
 int PI_PSTATUS_M_UNSOL_PENDING ; 
 int PI_PSTATUS_M_XMT_DATA_PENDING ; 
 int dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  dfx_int_common (struct net_device*) ; 
 int /*<<< orphan*/  dfx_port_read_long (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int inb (scalar_t__) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_eisa_device (struct device*) ; 

__attribute__((used)) static irqreturn_t dfx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	DFX_board_t *bp = netdev_priv(dev);
	struct device *bdev = bp->bus_dev;
	int dfx_bus_pci = dev_is_pci(bdev);
	int dfx_bus_eisa = DFX_BUS_EISA(bdev);
	int dfx_bus_tc = DFX_BUS_TC(bdev);

	/* Service adapter interrupts */

	if (dfx_bus_pci) {
		u32 status;

		dfx_port_read_long(bp, PFI_K_REG_STATUS, &status);
		if (!(status & PFI_STATUS_M_PDQ_INT))
			return IRQ_NONE;

		spin_lock(&bp->lock);

		/* Disable PDQ-PFI interrupts at PFI */
		dfx_port_write_long(bp, PFI_K_REG_MODE_CTRL,
				    PFI_MODE_M_DMA_ENB);

		/* Call interrupt service routine for this adapter */
		dfx_int_common(dev);

		/* Clear PDQ interrupt status bit and reenable interrupts */
		dfx_port_write_long(bp, PFI_K_REG_STATUS,
				    PFI_STATUS_M_PDQ_INT);
		dfx_port_write_long(bp, PFI_K_REG_MODE_CTRL,
				    (PFI_MODE_M_PDQ_INT_ENB |
				     PFI_MODE_M_DMA_ENB));

		spin_unlock(&bp->lock);
	}
	if (dfx_bus_eisa) {
		unsigned long base_addr = to_eisa_device(bdev)->base_addr;
		u8 status;

		status = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		if (!(status & PI_CONFIG_STAT_0_M_PEND))
			return IRQ_NONE;

		spin_lock(&bp->lock);

		/* Disable interrupts at the ESIC */
		status &= ~PI_CONFIG_STAT_0_M_INT_ENB;
		outb(status, base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);

		/* Call interrupt service routine for this adapter */
		dfx_int_common(dev);

		/* Reenable interrupts at the ESIC */
		status = inb(base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);
		status |= PI_CONFIG_STAT_0_M_INT_ENB;
		outb(status, base_addr + PI_ESIC_K_IO_CONFIG_STAT_0);

		spin_unlock(&bp->lock);
	}
	if (dfx_bus_tc) {
		u32 status;

		dfx_port_read_long(bp, PI_PDQ_K_REG_PORT_STATUS, &status);
		if (!(status & (PI_PSTATUS_M_RCV_DATA_PENDING |
				PI_PSTATUS_M_XMT_DATA_PENDING |
				PI_PSTATUS_M_SMT_HOST_PENDING |
				PI_PSTATUS_M_UNSOL_PENDING |
				PI_PSTATUS_M_CMD_RSP_PENDING |
				PI_PSTATUS_M_CMD_REQ_PENDING |
				PI_PSTATUS_M_TYPE_0_PENDING)))
			return IRQ_NONE;

		spin_lock(&bp->lock);

		/* Call interrupt service routine for this adapter */
		dfx_int_common(dev);

		spin_unlock(&bp->lock);
	}

	return IRQ_HANDLED;
}