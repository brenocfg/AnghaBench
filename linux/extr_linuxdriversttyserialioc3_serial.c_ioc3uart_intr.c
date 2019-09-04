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
struct ioc3_submodule {int dummy; } ;
struct ioc3_driver_data {int dummy; } ;

/* Variables and functions */
 unsigned int SIO_IR_SA ; 
 unsigned int SIO_IR_SB ; 
 int ioc3uart_intr_one (struct ioc3_submodule*,struct ioc3_driver_data*,unsigned int) ; 

__attribute__((used)) static int ioc3uart_intr(struct ioc3_submodule *is,
			struct ioc3_driver_data *idd,
			unsigned int pending)
{
	int ret = 0;

	/*
	 * The upper level interrupt handler sends interrupts for both ports
	 * here. So we need to call for each port with its interrupts.
	 */

	if (pending & SIO_IR_SA)
		ret |= ioc3uart_intr_one(is, idd, pending & SIO_IR_SA);
	if (pending & SIO_IR_SB)
		ret |= ioc3uart_intr_one(is, idd, pending & SIO_IR_SB);

	return ret;
}