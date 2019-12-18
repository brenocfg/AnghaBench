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
struct TYPE_3__ {int /*<<< orphan*/  pfile; } ;
typedef  TYPE_1__ LogicalTapeSet ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 scalar_t__ BufFileRead (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ BufFileSeekBlock (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,long) ; 

__attribute__((used)) static void
ltsReadBlock(LogicalTapeSet *lts, long blocknum, void *buffer)
{
	if (BufFileSeekBlock(lts->pfile, blocknum) != 0 ||
		BufFileRead(lts->pfile, buffer, BLCKSZ) != BLCKSZ)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not read block %ld of temporary file: %m",
						blocknum)));
}