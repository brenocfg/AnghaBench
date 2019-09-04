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
struct dio200_subdev_8255 {scalar_t__ ofs; } ;
struct comedi_subdevice {int io_bits; struct dio200_subdev_8255* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int I8255_CTRL_A_IO ; 
 int I8255_CTRL_B_IO ; 
 int I8255_CTRL_CW ; 
 int I8255_CTRL_C_HI_IO ; 
 int I8255_CTRL_C_LO_IO ; 
 scalar_t__ I8255_CTRL_REG ; 
 int /*<<< orphan*/  dio200_write8 (struct comedi_device*,scalar_t__,int) ; 

__attribute__((used)) static void dio200_subdev_8255_set_dir(struct comedi_device *dev,
				       struct comedi_subdevice *s)
{
	struct dio200_subdev_8255 *subpriv = s->private;
	int config;

	config = I8255_CTRL_CW;
	/* 1 in io_bits indicates output, 1 in config indicates input */
	if (!(s->io_bits & 0x0000ff))
		config |= I8255_CTRL_A_IO;
	if (!(s->io_bits & 0x00ff00))
		config |= I8255_CTRL_B_IO;
	if (!(s->io_bits & 0x0f0000))
		config |= I8255_CTRL_C_LO_IO;
	if (!(s->io_bits & 0xf00000))
		config |= I8255_CTRL_C_HI_IO;
	dio200_write8(dev, subpriv->ofs + I8255_CTRL_REG, config);
}