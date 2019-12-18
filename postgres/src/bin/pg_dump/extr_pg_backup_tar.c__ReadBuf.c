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
struct TYPE_4__ {size_t filePos; int /*<<< orphan*/  FH; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_5__ {scalar_t__ formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 size_t tarRead (void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_ReadBuf(ArchiveHandle *AH, void *buf, size_t len)
{
	lclContext *ctx = (lclContext *) AH->formatData;

	if (tarRead(buf, len, ctx->FH) != len)
		/* We already would have exited for errors on reads, must be EOF */
		fatal("could not read from input file: end of file");

	ctx->filePos += len;
	return;
}