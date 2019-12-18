#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ax25_call; } ;
typedef  TYPE_1__ ax25_address ;

/* Variables and functions */

void asc2ax(ax25_address *addr, const char *callsign)
{
	const char *s;
	int n;

	for (s = callsign, n = 0; n < 6; n++) {
		if (*s != '\0' && *s != '-')
			addr->ax25_call[n] = *s++;
		else
			addr->ax25_call[n] = ' ';
		addr->ax25_call[n] <<= 1;
		addr->ax25_call[n] &= 0xFE;
	}

	if (*s++ == '\0') {
		addr->ax25_call[6] = 0x00;
		return;
	}

	addr->ax25_call[6] = *s++ - '0';

	if (*s != '\0') {
		addr->ax25_call[6] *= 10;
		addr->ax25_call[6] += *s++ - '0';
	}

	addr->ax25_call[6] <<= 1;
	addr->ax25_call[6] &= 0x1E;
}