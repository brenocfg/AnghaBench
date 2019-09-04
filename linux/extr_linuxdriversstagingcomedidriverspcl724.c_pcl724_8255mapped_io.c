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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned long I8255_SIZE ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 

__attribute__((used)) static int pcl724_8255mapped_io(struct comedi_device *dev,
				int dir, int port, int data,
				unsigned long iobase)
{
	int movport = I8255_SIZE * (iobase >> 12);

	iobase &= 0x0fff;

	outb(port + movport, iobase);
	if (dir) {
		outb(data, iobase + 1);
		return 0;
	}
	return inb(iobase + 1);
}