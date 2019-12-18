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
typedef  int uint64 ;
typedef  int /*<<< orphan*/  macaddr ;

/* Variables and functions */

__attribute__((used)) static uint64
mac_2_uint64(macaddr *m)
{
	unsigned char *mi = (unsigned char *) m;
	uint64		res = 0;
	int			i;

	for (i = 0; i < 6; i++)
		res += (((uint64) mi[i]) << ((uint64) ((5 - i) * 8)));
	return res;
}