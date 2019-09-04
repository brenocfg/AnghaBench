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
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __i8254_write(struct comedi_8254 *i8254,
			  unsigned int val, unsigned int reg)
{
	unsigned int reg_offset = (reg * i8254->iosize) << i8254->regshift;

	switch (i8254->iosize) {
	default:
	case I8254_IO8:
		if (i8254->mmio)
			writeb(val, i8254->mmio + reg_offset);
		else
			outb(val, i8254->iobase + reg_offset);
		break;
	case I8254_IO16:
		if (i8254->mmio)
			writew(val, i8254->mmio + reg_offset);
		else
			outw(val, i8254->iobase + reg_offset);
		break;
	case I8254_IO32:
		if (i8254->mmio)
			writel(val, i8254->mmio + reg_offset);
		else
			outl(val, i8254->iobase + reg_offset);
		break;
	}
}