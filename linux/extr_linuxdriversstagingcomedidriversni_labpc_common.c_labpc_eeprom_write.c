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
 int /*<<< orphan*/  labpc_serial_out (struct comedi_device*,int const,int const) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void labpc_eeprom_write(struct comedi_device *dev,
			       unsigned int address, unsigned int value)
{
	struct labpc_private *devpriv = dev->private;
	const int write_enable_instruction = 0x6;
	const int write_instruction = 0x2;
	const int write_length = 8;	/*  8 bit write lengths to eeprom */

	/*  enable read/write to eeprom */
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
	devpriv->cmd5 |= (CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  send write_enable instruction */
	labpc_serial_out(dev, write_enable_instruction, write_length);
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  send write instruction */
	devpriv->cmd5 |= CMD5_EEPROMCS;
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
	labpc_serial_out(dev, write_instruction, write_length);
	/*  send 8 bit address to write to */
	labpc_serial_out(dev, address, write_length);
	/*  write value */
	labpc_serial_out(dev, value, write_length);
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  disable read/write to eeprom */
	devpriv->cmd5 &= ~(CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
}