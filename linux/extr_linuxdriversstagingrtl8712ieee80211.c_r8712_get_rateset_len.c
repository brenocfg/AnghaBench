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
typedef  size_t uint ;
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static uint r8712_get_rateset_len(u8 *rateset)
{
	uint i = 0;

	while (1) {
		if ((rateset[i]) == 0)
			break;
		if (i > 12)
			break;
		i++;
	}
	return i;
}