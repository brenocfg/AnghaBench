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
struct comedi_subdevice {int io_bits; } ;
struct comedi_device {unsigned long iobase; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int I8255_CTRL_A_IO ; 
 int I8255_CTRL_B_IO ; 
 int I8255_CTRL_CW ; 
 int I8255_CTRL_C_HI_IO ; 
 int I8255_CTRL_C_LO_IO ; 
 unsigned long I8255_CTRL_REG ; 
 unsigned long I8255_SIZE ; 
 unsigned long PCM3724_DIO_DIR_REG ; 
 int compute_buffer (int,int,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 

__attribute__((used)) static void do_3724_config(struct comedi_device *dev,
			   struct comedi_subdevice *s, int chanspec)
{
	struct comedi_subdevice *s_dio1 = &dev->subdevices[0];
	struct comedi_subdevice *s_dio2 = &dev->subdevices[1];
	int config;
	int buffer_config;
	unsigned long port_8255_cfg;

	config = I8255_CTRL_CW;
	buffer_config = 0;

	/* 1 in io_bits indicates output, 1 in config indicates input */
	if (!(s->io_bits & 0x0000ff))
		config |= I8255_CTRL_A_IO;

	if (!(s->io_bits & 0x00ff00))
		config |= I8255_CTRL_B_IO;

	if (!(s->io_bits & 0xff0000))
		config |= I8255_CTRL_C_HI_IO | I8255_CTRL_C_LO_IO;

	buffer_config = compute_buffer(0, 0, s_dio1);
	buffer_config = compute_buffer(buffer_config, 1, s_dio2);

	if (s == s_dio1)
		port_8255_cfg = dev->iobase + I8255_CTRL_REG;
	else
		port_8255_cfg = dev->iobase + I8255_SIZE + I8255_CTRL_REG;

	outb(buffer_config, dev->iobase + PCM3724_DIO_DIR_REG);

	outb(config, port_8255_cfg);
}