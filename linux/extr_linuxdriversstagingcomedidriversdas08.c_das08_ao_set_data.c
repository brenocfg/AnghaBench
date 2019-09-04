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
struct das08_board_struct {scalar_t__ is_jr; } ;
struct comedi_device {scalar_t__ iobase; struct das08_board_struct* board_ptr; } ;

/* Variables and functions */
 scalar_t__ DAS08AOX_AO_LSB_REG (unsigned int) ; 
 scalar_t__ DAS08AOX_AO_MSB_REG (unsigned int) ; 
 scalar_t__ DAS08AOX_AO_UPDATE_REG ; 
 scalar_t__ DAS08JR_AO_LSB_REG (unsigned int) ; 
 scalar_t__ DAS08JR_AO_MSB_REG (unsigned int) ; 
 scalar_t__ DAS08JR_AO_UPDATE_REG ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void das08_ao_set_data(struct comedi_device *dev,
			      unsigned int chan, unsigned int data)
{
	const struct das08_board_struct *board = dev->board_ptr;
	unsigned char lsb;
	unsigned char msb;

	lsb = data & 0xff;
	msb = (data >> 8) & 0xff;
	if (board->is_jr) {
		outb(lsb, dev->iobase + DAS08JR_AO_LSB_REG(chan));
		outb(msb, dev->iobase + DAS08JR_AO_MSB_REG(chan));
		/* load DACs */
		inb(dev->iobase + DAS08JR_AO_UPDATE_REG);
	} else {
		outb(lsb, dev->iobase + DAS08AOX_AO_LSB_REG(chan));
		outb(msb, dev->iobase + DAS08AOX_AO_MSB_REG(chan));
		/* load DACs */
		inb(dev->iobase + DAS08AOX_AO_UPDATE_REG);
	}
}