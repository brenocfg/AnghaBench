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
struct labpc_private {int /*<<< orphan*/  cmd5; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD5_REG ; 
 int /*<<< orphan*/  CMD5_SCLK ; 
 int /*<<< orphan*/  CMD5_SDATA ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void labpc_serial_out(struct comedi_device *dev, unsigned int value,
			     unsigned int value_width)
{
	struct labpc_private *devpriv = dev->private;
	int i;

	for (i = 1; i <= value_width; i++) {
		/*  clear serial clock */
		devpriv->cmd5 &= ~CMD5_SCLK;
		/*  send bits most significant bit first */
		if (value & (1 << (value_width - i)))
			devpriv->cmd5 |= CMD5_SDATA;
		else
			devpriv->cmd5 &= ~CMD5_SDATA;
		udelay(1);
		devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
		/*  set clock to load bit */
		devpriv->cmd5 |= CMD5_SCLK;
		udelay(1);
		devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
	}
}