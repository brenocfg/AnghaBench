#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * blobsTocFH; } ;
typedef  TYPE_1__ lclContext ;
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_6__ {scalar_t__ formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/ * cfopen_write (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 int /*<<< orphan*/  setFilePath (TYPE_2__*,char*,char*) ; 

__attribute__((used)) static void
_StartBlobs(ArchiveHandle *AH, TocEntry *te)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	char		fname[MAXPGPATH];

	setFilePath(AH, fname, "blobs.toc");

	/* The blob TOC file is never compressed */
	ctx->blobsTocFH = cfopen_write(fname, "ab", 0);
	if (ctx->blobsTocFH == NULL)
		fatal("could not open output file \"%s\": %m", fname);
}