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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static u32 add_byte(u32 **p_buffer, u8 value, u32 *used, u32 *avail)
{
	u8 **tByte;

	if ((*used + 1) > *avail)
		return(1);

	*((u8 *)*p_buffer) = value;
	tByte = (u8 **)p_buffer;
	(*tByte)++;
	*used += 1;
	return(0);
}