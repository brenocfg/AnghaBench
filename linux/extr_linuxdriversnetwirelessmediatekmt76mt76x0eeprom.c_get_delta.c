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
typedef  int s8 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  field_valid (int) ; 

__attribute__((used)) static s8
get_delta(u8 val)
{
	s8 ret;

	if (!field_valid(val) || !(val & BIT(7)))
		return 0;

	ret = val & 0x1f;
	if (ret > 8)
		ret = 8;
	if (val & BIT(6))
		ret = -ret;

	return ret;
}