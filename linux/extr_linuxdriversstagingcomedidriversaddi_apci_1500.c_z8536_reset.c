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
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI1500_Z8536_CTRL_REG ; 
 int /*<<< orphan*/  Z8536_CFG_CTRL_REG ; 
 int Z8536_CMD_CLR_IE ; 
 int Z8536_CMD_CLR_IP_IUS ; 
 int /*<<< orphan*/  Z8536_CT_CMDSTAT_REG (int) ; 
 int /*<<< orphan*/  Z8536_INT_CTRL_REG ; 
 int Z8536_PAB_MODE_PMS_DISABLE ; 
 int Z8536_PAB_MODE_PTS_BIT ; 
 int Z8536_PAB_MODE_SB ; 
 int /*<<< orphan*/  Z8536_PA_CMDSTAT_REG ; 
 int /*<<< orphan*/  Z8536_PA_DD_REG ; 
 int /*<<< orphan*/  Z8536_PA_MODE_REG ; 
 int /*<<< orphan*/  Z8536_PB_CMDSTAT_REG ; 
 int /*<<< orphan*/  Z8536_PB_DD_REG ; 
 int /*<<< orphan*/  Z8536_PB_DPP_REG ; 
 int /*<<< orphan*/  Z8536_PB_MODE_REG ; 
 int /*<<< orphan*/  Z8536_PC_DD_REG ; 
 int /*<<< orphan*/  Z8536_PC_DPP_REG ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  z8536_write (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void z8536_reset(struct comedi_device *dev)
{
	unsigned long flags;

	/*
	 * Even if the state of the Z8536 is not known, the following
	 * sequence will reset it and put it in State 0.
	 */
	spin_lock_irqsave(&dev->spinlock, flags);
	inb(dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(0, dev->iobase + APCI1500_Z8536_CTRL_REG);
	inb(dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(0, dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(1, dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(0, dev->iobase + APCI1500_Z8536_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* Disable all Ports and Counter/Timers */
	z8536_write(dev, 0x00, Z8536_CFG_CTRL_REG);

	/*
	 * Port A is connected to Ditial Input channels 0-7.
	 * Configure the port to allow interrupt detection.
	 */
	z8536_write(dev, Z8536_PAB_MODE_PTS_BIT |
			 Z8536_PAB_MODE_SB |
			 Z8536_PAB_MODE_PMS_DISABLE,
		    Z8536_PA_MODE_REG);
	z8536_write(dev, 0xff, Z8536_PB_DPP_REG);
	z8536_write(dev, 0xff, Z8536_PA_DD_REG);

	/*
	 * Port B is connected to Ditial Input channels 8-13.
	 * Configure the port to allow interrupt detection.
	 *
	 * NOTE: Bits 7 and 6 of Port B are connected to internal
	 * diagnostic signals and bit 7 is inverted.
	 */
	z8536_write(dev, Z8536_PAB_MODE_PTS_BIT |
			 Z8536_PAB_MODE_SB |
			 Z8536_PAB_MODE_PMS_DISABLE,
		    Z8536_PB_MODE_REG);
	z8536_write(dev, 0x7f, Z8536_PB_DPP_REG);
	z8536_write(dev, 0xff, Z8536_PB_DD_REG);

	/*
	 * Not sure what Port C is connected to...
	 */
	z8536_write(dev, 0x09, Z8536_PC_DPP_REG);
	z8536_write(dev, 0x0e, Z8536_PC_DD_REG);

	/*
	 * Clear and disable all interrupt sources.
	 *
	 * Just in case, the reset of the Z8536 should have already
	 * done this.
	 */
	z8536_write(dev, Z8536_CMD_CLR_IP_IUS, Z8536_PA_CMDSTAT_REG);
	z8536_write(dev, Z8536_CMD_CLR_IE, Z8536_PA_CMDSTAT_REG);

	z8536_write(dev, Z8536_CMD_CLR_IP_IUS, Z8536_PB_CMDSTAT_REG);
	z8536_write(dev, Z8536_CMD_CLR_IE, Z8536_PB_CMDSTAT_REG);

	z8536_write(dev, Z8536_CMD_CLR_IP_IUS, Z8536_CT_CMDSTAT_REG(0));
	z8536_write(dev, Z8536_CMD_CLR_IE, Z8536_CT_CMDSTAT_REG(0));

	z8536_write(dev, Z8536_CMD_CLR_IP_IUS, Z8536_CT_CMDSTAT_REG(1));
	z8536_write(dev, Z8536_CMD_CLR_IE, Z8536_CT_CMDSTAT_REG(1));

	z8536_write(dev, Z8536_CMD_CLR_IP_IUS, Z8536_CT_CMDSTAT_REG(2));
	z8536_write(dev, Z8536_CMD_CLR_IE, Z8536_CT_CMDSTAT_REG(2));

	/* Disable all interrupts */
	z8536_write(dev, 0x00, Z8536_INT_CTRL_REG);
}