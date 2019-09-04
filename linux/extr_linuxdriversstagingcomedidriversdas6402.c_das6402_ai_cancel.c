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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAS6402_CTRL_REG ; 
 int /*<<< orphan*/  DAS6402_CTRL_SOFT_TRIG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int das6402_ai_cancel(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	outb(DAS6402_CTRL_SOFT_TRIG, dev->iobase + DAS6402_CTRL_REG);

	return 0;
}