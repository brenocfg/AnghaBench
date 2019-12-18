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
struct sbitmap {unsigned int shift; unsigned int map_nr; unsigned int depth; TYPE_1__* map; } ;
struct TYPE_2__ {scalar_t__ depth; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 scalar_t__ min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sbitmap_deferred_clear (struct sbitmap*,unsigned int) ; 

void sbitmap_resize(struct sbitmap *sb, unsigned int depth)
{
	unsigned int bits_per_word = 1U << sb->shift;
	unsigned int i;

	for (i = 0; i < sb->map_nr; i++)
		sbitmap_deferred_clear(sb, i);

	sb->depth = depth;
	sb->map_nr = DIV_ROUND_UP(sb->depth, bits_per_word);

	for (i = 0; i < sb->map_nr; i++) {
		sb->map[i].depth = min(depth, bits_per_word);
		depth -= sb->map[i].depth;
	}
}