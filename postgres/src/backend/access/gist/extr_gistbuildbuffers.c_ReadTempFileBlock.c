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
 scalar_t__ BufFileRead (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 scalar_t__ BufFileSeekBlock (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ReadTempFileBlock(BufFile *file, long blknum, void *ptr)
{
	if (BufFileSeekBlock(file, blknum) != 0)
		elog(ERROR, "could not seek temporary file: %m");
	if (BufFileRead(file, ptr, BLCKSZ) != BLCKSZ)
		elog(ERROR, "could not read temporary file: %m");
}