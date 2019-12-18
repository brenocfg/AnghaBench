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

unsigned int bitmask_next(const struct bitmask *bmp, unsigned int i)
{
	unsigned int n;
	for (n = i; n < bmp->size; n++)
		if (_getbit(bmp, n))
			break;
	return n;
}