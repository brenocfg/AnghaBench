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
struct ioc3_driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nic_read_bit (struct ioc3_driver_data*) ; 
 int /*<<< orphan*/  nic_reset (struct ioc3_driver_data*) ; 
 int /*<<< orphan*/  nic_write_bit (struct ioc3_driver_data*,unsigned long) ; 
 int /*<<< orphan*/  nic_write_byte (struct ioc3_driver_data*,int) ; 

__attribute__((used)) static void nic_addr(struct ioc3_driver_data *idd, unsigned long addr)
{
	int index;

	nic_reset(idd);
	nic_write_byte(idd, 0xF0);
	for (index = 0; index < 64; index++) {
		nic_read_bit(idd);
		nic_read_bit(idd);
		nic_write_bit(idd, (addr>>index)&1);
	}
}