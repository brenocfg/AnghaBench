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
typedef  scalar_t__ u8 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16 ar9300_comp_cksum(u8 *data, int dsize)
{
	int it, checksum = 0;

	for (it = 0; it < dsize; it++) {
		checksum += data[it];
		checksum &= 0xffff;
	}

	return checksum;
}