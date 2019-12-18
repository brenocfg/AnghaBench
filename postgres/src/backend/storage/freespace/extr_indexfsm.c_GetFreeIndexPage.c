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
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int BLCKSZ ; 
 scalar_t__ GetPageWithFreeSpace (int /*<<< orphan*/ ,int) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  RecordUsedIndexPage (int /*<<< orphan*/ ,scalar_t__) ; 

BlockNumber
GetFreeIndexPage(Relation rel)
{
	BlockNumber blkno = GetPageWithFreeSpace(rel, BLCKSZ / 2);

	if (blkno != InvalidBlockNumber)
		RecordUsedIndexPage(rel, blkno);

	return blkno;
}