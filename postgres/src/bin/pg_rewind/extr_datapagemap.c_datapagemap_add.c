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
struct TYPE_3__ {int bitmapsize; int* bitmap; } ;
typedef  TYPE_1__ datapagemap_t ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* pg_realloc (int*,int) ; 

void
datapagemap_add(datapagemap_t *map, BlockNumber blkno)
{
	int			offset;
	int			bitno;

	offset = blkno / 8;
	bitno = blkno % 8;

	/* enlarge or create bitmap if needed */
	if (map->bitmapsize <= offset)
	{
		int			oldsize = map->bitmapsize;
		int			newsize;

		/*
		 * The minimum to hold the new bit is offset + 1. But add some
		 * headroom, so that we don't need to repeatedly enlarge the bitmap in
		 * the common case that blocks are modified in order, from beginning
		 * of a relation to the end.
		 */
		newsize = offset + 1;
		newsize += 10;

		map->bitmap = pg_realloc(map->bitmap, newsize);

		/* zero out the newly allocated region */
		memset(&map->bitmap[oldsize], 0, newsize - oldsize);

		map->bitmapsize = newsize;
	}

	/* Set the bit */
	map->bitmap[offset] |= (1 << bitno);
}