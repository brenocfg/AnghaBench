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
struct bitmask {unsigned int size; } ;

/* Variables and functions */
 scalar_t__ _getbit (struct bitmask const*,unsigned int) ; 

int bitmask_isallclear(const struct bitmask *bmp)
{
	unsigned int i;
	for (i = 0; i < bmp->size; i++)
		if (_getbit(bmp, i))
			return 0;
	return 1;
}