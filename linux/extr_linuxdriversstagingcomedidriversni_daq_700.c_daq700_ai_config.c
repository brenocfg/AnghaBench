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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {unsigned long iobase; } ;

/* Variables and functions */
 scalar_t__ ADCLEAR_R ; 
 scalar_t__ ADFIFO_R ; 
 scalar_t__ CMD_R1 ; 
 scalar_t__ CMD_R2 ; 
 scalar_t__ CMD_R3 ; 
 scalar_t__ CMO_R ; 
 scalar_t__ TIC_R ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void daq700_ai_config(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	unsigned long iobase = dev->iobase;

	outb(0x80, iobase + CMD_R1);	/* disable scanning, ADC to chan 0 */
	outb(0x00, iobase + CMD_R2);	/* clear all bits */
	outb(0x00, iobase + CMD_R3);	/* set +-10 range */
	outb(0x32, iobase + CMO_R);	/* config counter mode1, out0 to H */
	outb(0x00, iobase + TIC_R);	/* clear counter interrupt */
	outb(0x00, iobase + ADCLEAR_R);	/* clear the ADC FIFO */
	inw(iobase + ADFIFO_R);		/* read 16bit junk from FIFO to clear */
}