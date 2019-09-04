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
 scalar_t__ DAS6402_STATUS_REG ; 
 unsigned int DAS6402_STATUS_W_EXTEND ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void das6402_set_extended(struct comedi_device *dev,
				 unsigned int val)
{
	outb(DAS6402_STATUS_W_EXTEND, dev->iobase + DAS6402_STATUS_REG);
	outb(DAS6402_STATUS_W_EXTEND | val, dev->iobase + DAS6402_STATUS_REG);
	outb(val, dev->iobase + DAS6402_STATUS_REG);
}