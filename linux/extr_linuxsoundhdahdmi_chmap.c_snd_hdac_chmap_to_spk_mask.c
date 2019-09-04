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
struct channel_map_table {char map; int spk_mask; } ;

/* Variables and functions */
 struct channel_map_table* map_tables ; 

int snd_hdac_chmap_to_spk_mask(unsigned char c)
{
	struct channel_map_table *t = map_tables;

	for (; t->map; t++) {
		if (t->map == c)
			return t->spk_mask;
	}
	return 0;
}