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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S626_DIO_BANKS ; 
 int /*<<< orphan*/  S626_LP_RDCAPFLG (scalar_t__) ; 
 scalar_t__ s626_debi_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_handle_dio_interrupt (struct comedi_device*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void s626_check_dio_interrupts(struct comedi_device *dev)
{
	u16 irqbit;
	u8 group;

	for (group = 0; group < S626_DIO_BANKS; group++) {
		/* read interrupt type */
		irqbit = s626_debi_read(dev, S626_LP_RDCAPFLG(group));

		/* check if interrupt is generated from dio channels */
		if (irqbit) {
			s626_handle_dio_interrupt(dev, irqbit, group);
			return;
		}
	}
}