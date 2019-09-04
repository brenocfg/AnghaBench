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
typedef  int u32 ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int nic_read_bit (struct ioc3*) ; 

__attribute__((used)) static u32 nic_read_byte(struct ioc3 *ioc3)
{
	u32 result = 0;
	int i;

	for (i = 0; i < 8; i++)
		result = (result >> 1) | (nic_read_bit(ioc3) << 7);

	return result;
}