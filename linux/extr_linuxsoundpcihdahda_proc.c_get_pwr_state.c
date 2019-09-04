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
typedef  size_t u32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 

__attribute__((used)) static const char *get_pwr_state(u32 state)
{
	static const char * const buf[] = {
		"D0", "D1", "D2", "D3", "D3cold"
	};
	if (state < ARRAY_SIZE(buf))
		return buf[state];
	return "UNKNOWN";
}