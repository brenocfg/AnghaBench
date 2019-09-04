#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* ax25_call; } ;
typedef  TYPE_1__ ax25_address ;

/* Variables and functions */

int ax25cmp(const ax25_address *a, const ax25_address *b)
{
	int ct = 0;

	while (ct < 6) {
		if ((a->ax25_call[ct] & 0xFE) != (b->ax25_call[ct] & 0xFE))	/* Clean off repeater bits */
			return 1;
		ct++;
	}

	if ((a->ax25_call[ct] & 0x1E) == (b->ax25_call[ct] & 0x1E))	/* SSID without control bit */
		return 0;

	return 2;			/* Partial match */
}