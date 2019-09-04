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
 unsigned int S626_DIO_BANKS ; 
 int /*<<< orphan*/  S626_LP_MISC1 ; 
 int /*<<< orphan*/  S626_LP_WRCAPSEL (unsigned int) ; 
 int S626_MISC1_NOEDCAP ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s626_dio_clear_irq(struct comedi_device *dev)
{
	unsigned int group;

	/* disable edge capture write command */
	s626_debi_write(dev, S626_LP_MISC1, S626_MISC1_NOEDCAP);

	/* clear all dio pending events and interrupt */
	for (group = 0; group < S626_DIO_BANKS; group++)
		s626_debi_write(dev, S626_LP_WRCAPSEL(group), 0xffff);

	return 0;
}