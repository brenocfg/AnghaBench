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
typedef  int uint8 ;

/* Variables and functions */
 int s2k_decode_count (int) ; 

__attribute__((used)) static uint8
decide_s2k_iter(unsigned rand_byte, int count)
{
	int			iter;

	if (count == -1)
		return 96 + (rand_byte & 0x1F);
	/* this is a bit brute-force, but should be quick enough */
	for (iter = 0; iter <= 255; iter++)
		if (s2k_decode_count(iter) >= count)
			return iter;
	return 255;
}