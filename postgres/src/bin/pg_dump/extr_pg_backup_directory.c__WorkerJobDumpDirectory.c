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
typedef  int /*<<< orphan*/  TocEntry ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  WriteDataChunksForTocEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_WorkerJobDumpDirectory(ArchiveHandle *AH, TocEntry *te)
{
	/*
	 * This function returns void. We either fail and die horribly or
	 * succeed... A failure will be detected by the parent when the child dies
	 * unexpectedly.
	 */
	WriteDataChunksForTocEntry(AH, te);

	return 0;
}