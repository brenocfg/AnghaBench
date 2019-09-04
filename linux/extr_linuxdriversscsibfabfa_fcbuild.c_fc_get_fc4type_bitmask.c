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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

void
fc_get_fc4type_bitmask(u8 fc4_type, u8 *bit_mask)
{
	u8         index;
	__be32       *ptr = (__be32 *) bit_mask;
	u32        type_value;

	/*
	 * @todo : Check for bitmask size
	 */

	index = fc4_type >> 5;
	type_value = 1 << (fc4_type % 32);
	ptr[index] = cpu_to_be32(type_value);

}