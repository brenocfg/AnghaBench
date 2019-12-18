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
struct sbitmap {int shift; unsigned int depth; unsigned int map_nr; TYPE_1__* map; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  swap_lock; scalar_t__ depth; } ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ilog2 (unsigned int) ; 
 TYPE_1__* kcalloc_node (unsigned int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int sbitmap_init_node(struct sbitmap *sb, unsigned int depth, int shift,
		      gfp_t flags, int node)
{
	unsigned int bits_per_word;
	unsigned int i;

	if (shift < 0) {
		shift = ilog2(BITS_PER_LONG);
		/*
		 * If the bitmap is small, shrink the number of bits per word so
		 * we spread over a few cachelines, at least. If less than 4
		 * bits, just forget about it, it's not going to work optimally
		 * anyway.
		 */
		if (depth >= 4) {
			while ((4U << shift) > depth)
				shift--;
		}
	}
	bits_per_word = 1U << shift;
	if (bits_per_word > BITS_PER_LONG)
		return -EINVAL;

	sb->shift = shift;
	sb->depth = depth;
	sb->map_nr = DIV_ROUND_UP(sb->depth, bits_per_word);

	if (depth == 0) {
		sb->map = NULL;
		return 0;
	}

	sb->map = kcalloc_node(sb->map_nr, sizeof(*sb->map), flags, node);
	if (!sb->map)
		return -ENOMEM;

	for (i = 0; i < sb->map_nr; i++) {
		sb->map[i].depth = min(depth, bits_per_word);
		depth -= sb->map[i].depth;
		spin_lock_init(&sb->map[i].swap_lock);
	}
	return 0;
}