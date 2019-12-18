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
typedef  int /*<<< orphan*/  BufFile ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 scalar_t__ BufFileSeekBlock (int /*<<< orphan*/ *,long) ; 
 scalar_t__ BufFileWrite (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,long) ; 

__attribute__((used)) static void
WriteTempFileBlock(BufFile *file, long blknum, void *ptr)
{
	if (BufFileSeekBlock(file, blknum) != 0)
		elog(ERROR, "could not seek temporary file: %m");
	if (BufFileWrite(file, ptr, BLCKSZ) != BLCKSZ)
	{
		/*
		 * the other errors in Read/WriteTempFileBlock shouldn't happen, but
		 * an error at write can easily happen if you run out of disk space.
		 */
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not write block %ld of temporary file: %m",
						blknum)));
	}
}