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
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct bmap {int db_numag; int db_agpref; int* db_agfree; int /*<<< orphan*/ * db_active; scalar_t__ db_nfree; } ;
typedef  int s64 ;
struct TYPE_2__ {struct bmap* bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAP_LOCK (struct bmap*) ; 
 int /*<<< orphan*/  BMAP_UNLOCK (struct bmap*) ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

int dbNextAG(struct inode *ipbmap)
{
	s64 avgfree;
	int agpref;
	s64 hwm = 0;
	int i;
	int next_best = -1;
	struct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;

	BMAP_LOCK(bmp);

	/* determine the average number of free blocks within the ags. */
	avgfree = (u32)bmp->db_nfree / bmp->db_numag;

	/*
	 * if the current preferred ag does not have an active allocator
	 * and has at least average freespace, return it
	 */
	agpref = bmp->db_agpref;
	if ((atomic_read(&bmp->db_active[agpref]) == 0) &&
	    (bmp->db_agfree[agpref] >= avgfree))
		goto unlock;

	/* From the last preferred ag, find the next one with at least
	 * average free space.
	 */
	for (i = 0 ; i < bmp->db_numag; i++, agpref++) {
		if (agpref == bmp->db_numag)
			agpref = 0;

		if (atomic_read(&bmp->db_active[agpref]))
			/* open file is currently growing in this ag */
			continue;
		if (bmp->db_agfree[agpref] >= avgfree) {
			/* Return this one */
			bmp->db_agpref = agpref;
			goto unlock;
		} else if (bmp->db_agfree[agpref] > hwm) {
			/* Less than avg. freespace, but best so far */
			hwm = bmp->db_agfree[agpref];
			next_best = agpref;
		}
	}

	/*
	 * If no inactive ag was found with average freespace, use the
	 * next best
	 */
	if (next_best != -1)
		bmp->db_agpref = next_best;
	/* else leave db_agpref unchanged */
unlock:
	BMAP_UNLOCK(bmp);

	/* return the preferred group.
	 */
	return (bmp->db_agpref);
}