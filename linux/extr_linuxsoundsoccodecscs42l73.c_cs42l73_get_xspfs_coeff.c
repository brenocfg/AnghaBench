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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* cs42l73_asrc_rates ; 

__attribute__((used)) static unsigned int cs42l73_get_xspfs_coeff(u32 rate)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(cs42l73_asrc_rates); i++) {
		if (cs42l73_asrc_rates[i] == rate)
			return i + 1;
	}
	return 0;		/* 0 = Don't know */
}