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
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAS16M1_CS_REG ; 
 int comedi_buf_n_bytes_ready (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das16m1_handler (struct comedi_device*,unsigned int) ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int das16m1_ai_poll(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	unsigned long flags;
	unsigned int status;

	/*  prevent race with interrupt handler */
	spin_lock_irqsave(&dev->spinlock, flags);
	status = inb(dev->iobase + DAS16M1_CS_REG);
	das16m1_handler(dev, status);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return comedi_buf_n_bytes_ready(s);
}