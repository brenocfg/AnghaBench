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
typedef  int uint ;
typedef  scalar_t__ u8 ;

/* Variables and functions */

uint rtw_get_rateset_len(u8 *rateset)
{
	uint i;

	for (i = 0; i < 13; i++)
		if (rateset[i] == 0)
			break;
	return i;
}