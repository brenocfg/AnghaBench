#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bitmapsize; int* bitmap; } ;
typedef  TYPE_1__ datapagemap_t ;
struct TYPE_5__ {int nextblkno; TYPE_1__* map; } ;
typedef  TYPE_2__ datapagemap_iterator_t ;
typedef  int BlockNumber ;

/* Variables and functions */

bool
datapagemap_next(datapagemap_iterator_t *iter, BlockNumber *blkno)
{
	datapagemap_t *map = iter->map;

	for (;;)
	{
		BlockNumber blk = iter->nextblkno;
		int			nextoff = blk / 8;
		int			bitno = blk % 8;

		if (nextoff >= map->bitmapsize)
			break;

		iter->nextblkno++;

		if (map->bitmap[nextoff] & (1 << bitno))
		{
			*blkno = blk;
			return true;
		}
	}

	/* no more set bits in this bitmap. */
	return false;
}