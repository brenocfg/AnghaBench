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
struct TYPE_3__ {scalar_t__ rm_lastRevmapPage; int /*<<< orphan*/  rm_pagesPerRange; } ;
typedef  TYPE_1__ BrinRevmap ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ HEAPBLK_TO_REVMAP_BLK (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 

__attribute__((used)) static BlockNumber
revmap_get_blkno(BrinRevmap *revmap, BlockNumber heapBlk)
{
	BlockNumber targetblk;

	/* obtain revmap block number, skip 1 for metapage block */
	targetblk = HEAPBLK_TO_REVMAP_BLK(revmap->rm_pagesPerRange, heapBlk) + 1;

	/* Normal case: the revmap page is already allocated */
	if (targetblk <= revmap->rm_lastRevmapPage)
		return targetblk;

	return InvalidBlockNumber;
}