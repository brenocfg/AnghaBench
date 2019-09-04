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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAS800_GAIN ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static unsigned int das800_ind_read(struct comedi_device *dev, unsigned int reg)
{
	/*
	 * Select dev->iobase + 7 to be desired register
	 * then read from that register.
	 */
	outb(reg, dev->iobase + DAS800_GAIN);
	return inb(dev->iobase + 7);
}