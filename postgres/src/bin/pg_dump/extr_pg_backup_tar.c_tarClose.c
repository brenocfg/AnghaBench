#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ compression; } ;
struct TYPE_7__ {char mode; int /*<<< orphan*/ * zFH; int /*<<< orphan*/ * nFH; scalar_t__ targetFile; } ;
typedef  TYPE_1__ TAR_MEMBER ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ GZCLOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tarAddFile (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void
tarClose(ArchiveHandle *AH, TAR_MEMBER *th)
{
	/*
	 * Close the GZ file since we dup'd. This will flush the buffers.
	 */
	if (AH->compression != 0)
		if (GZCLOSE(th->zFH) != 0)
			fatal("could not close tar member");

	if (th->mode == 'w')
		_tarAddFile(AH, th);	/* This will close the temp file */

	/*
	 * else Nothing to do for normal read since we don't dup() normal file
	 * handle, and we don't use temp files.
	 */

	if (th->targetFile)
		free(th->targetFile);

	th->nFH = NULL;
	th->zFH = NULL;
}