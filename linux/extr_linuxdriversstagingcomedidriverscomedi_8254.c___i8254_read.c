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
struct comedi_8254 {unsigned int iosize; unsigned int regshift; int /*<<< orphan*/  iobase; int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
#define  I8254_IO16 130 
#define  I8254_IO32 129 
#define  I8254_IO8 128 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 unsigned int inw (int /*<<< orphan*/ ) ; 
 unsigned int readb (int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 unsigned int readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __i8254_read(struct comedi_8254 *i8254, unsigned int reg)
{
	unsigned int reg_offset = (reg * i8254->iosize) << i8254->regshift;
	unsigned int val;

	switch (i8254->iosize) {
	default:
	case I8254_IO8:
		if (i8254->mmio)
			val = readb(i8254->mmio + reg_offset);
		else
			val = inb(i8254->iobase + reg_offset);
		break;
	case I8254_IO16:
		if (i8254->mmio)
			val = readw(i8254->mmio + reg_offset);
		else
			val = inw(i8254->iobase + reg_offset);
		break;
	case I8254_IO32:
		if (i8254->mmio)
			val = readl(i8254->mmio + reg_offset);
		else
			val = inl(i8254->iobase + reg_offset);
		break;
	}
	return val & 0xff;
}