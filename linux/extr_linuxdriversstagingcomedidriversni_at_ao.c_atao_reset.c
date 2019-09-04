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
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct atao_private* private; } ;
struct atao_private {scalar_t__ cfg3; scalar_t__ cfg1; } ;

/* Variables and functions */
 scalar_t__ ATAO_2_DMATCCLR_REG ; 
 scalar_t__ ATAO_2_INT1CLR_REG ; 
 scalar_t__ ATAO_2_INT2CLR_REG ; 
 scalar_t__ ATAO_CFG1_REG ; 
 scalar_t__ ATAO_CFG2_CALLD_NOP ; 
 scalar_t__ ATAO_CFG2_REG ; 
 scalar_t__ ATAO_CFG3_REG ; 
 scalar_t__ ATAO_FIFO_CLEAR_REG ; 
 int I8254_BINARY ; 
 int I8254_MODE4 ; 
 int /*<<< orphan*/  atao_select_reg_group (struct comedi_device*,int) ; 
 int /*<<< orphan*/  comedi_8254_set_mode (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  comedi_8254_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void atao_reset(struct comedi_device *dev)
{
	struct atao_private *devpriv = dev->private;

	/* This is the reset sequence described in the manual */

	devpriv->cfg1 = 0;
	outw(devpriv->cfg1, dev->iobase + ATAO_CFG1_REG);

	/* Put outputs of counter 1 and counter 2 in a high state */
	comedi_8254_set_mode(dev->pacer, 0, I8254_MODE4 | I8254_BINARY);
	comedi_8254_set_mode(dev->pacer, 1, I8254_MODE4 | I8254_BINARY);
	comedi_8254_write(dev->pacer, 0, 0x0003);

	outw(ATAO_CFG2_CALLD_NOP, dev->iobase + ATAO_CFG2_REG);

	devpriv->cfg3 = 0;
	outw(devpriv->cfg3, dev->iobase + ATAO_CFG3_REG);

	inw(dev->iobase + ATAO_FIFO_CLEAR_REG);

	atao_select_reg_group(dev, 1);
	outw(0, dev->iobase + ATAO_2_INT1CLR_REG);
	outw(0, dev->iobase + ATAO_2_INT2CLR_REG);
	outw(0, dev->iobase + ATAO_2_DMATCCLR_REG);
	atao_select_reg_group(dev, 0);
}