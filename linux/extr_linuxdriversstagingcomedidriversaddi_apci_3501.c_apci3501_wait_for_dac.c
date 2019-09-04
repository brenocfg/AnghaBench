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
 scalar_t__ APCI3501_AO_CTRL_STATUS_REG ; 
 unsigned int APCI3501_AO_STATUS_READY ; 
 unsigned int inl (scalar_t__) ; 

__attribute__((used)) static int apci3501_wait_for_dac(struct comedi_device *dev)
{
	unsigned int status;

	do {
		status = inl(dev->iobase + APCI3501_AO_CTRL_STATUS_REG);
	} while (!(status & APCI3501_AO_STATUS_READY));

	return 0;
}