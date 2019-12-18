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
typedef  size_t u8 ;

/* Variables and functions */

__attribute__((used)) static void mrp_attrvalue_inc(void *value, u8 len)
{
	u8 *v = (u8 *)value;

	/* Add 1 to the last byte. If it becomes zero,
	 * go to the previous byte and repeat.
	 */
	while (len > 0 && !++v[--len])
		;
}