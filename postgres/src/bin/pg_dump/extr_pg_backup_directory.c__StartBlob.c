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
struct TYPE_4__ {char* directory; int /*<<< orphan*/ * dataFH; } ;
typedef  TYPE_1__ lclContext ;
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_5__ {int /*<<< orphan*/  compression; scalar_t__ formatData; } ;
typedef  int Oid ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 int /*<<< orphan*/ * cfopen_write (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void
_StartBlob(ArchiveHandle *AH, TocEntry *te, Oid oid)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	char		fname[MAXPGPATH];

	snprintf(fname, MAXPGPATH, "%s/blob_%u.dat", ctx->directory, oid);

	ctx->dataFH = cfopen_write(fname, PG_BINARY_W, AH->compression);

	if (ctx->dataFH == NULL)
		fatal("could not open output file \"%s\": %m", fname);
}