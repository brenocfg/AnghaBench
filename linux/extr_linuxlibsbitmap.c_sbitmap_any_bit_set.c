#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbitmap {unsigned int map_nr; TYPE_1__* map; } ;
struct TYPE_2__ {scalar_t__ word; } ;

/* Variables and functions */

bool sbitmap_any_bit_set(const struct sbitmap *sb)
{
	unsigned int i;

	for (i = 0; i < sb->map_nr; i++) {
		if (sb->map[i].word)
			return true;
	}
	return false;
}