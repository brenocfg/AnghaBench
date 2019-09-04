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
struct labpc_private {int cmd5; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int CMD5_EEPROMCS ; 
 int /*<<< orphan*/  CMD5_REG ; 
 int CMD5_WRTPRT ; 
 unsigned int labpc_serial_in (struct comedi_device*) ; 
 int /*<<< orphan*/  labpc_serial_out (struct comedi_device*,int const,int const) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int labpc_eeprom_read_status(struct comedi_device *dev)
{
	struct labpc_private *devpriv = dev->private;
	unsigned int value;
	const int read_status_instruction = 0x5;
	const int write_length = 8;	/*  8 bit write lengths to eeprom */

	/*  enable read/write to eeprom */
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
	devpriv->cmd5 |= (CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  send read status instruction */
	labpc_serial_out(dev, read_status_instruction, write_length);
	/*  read result */
	value = labpc_serial_in(dev);

	/*  disable read/write to eeprom */
	devpriv->cmd5 &= ~(CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);

	return value;
}