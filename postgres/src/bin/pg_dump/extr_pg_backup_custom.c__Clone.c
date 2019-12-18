#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * cs; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_7__ {TYPE_1__* formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ pg_malloc (int) ; 

__attribute__((used)) static void
_Clone(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;

	AH->formatData = (lclContext *) pg_malloc(sizeof(lclContext));
	memcpy(AH->formatData, ctx, sizeof(lclContext));
	ctx = (lclContext *) AH->formatData;

	/* sanity check, shouldn't happen */
	if (ctx->cs != NULL)
		fatal("compressor active");

	/*
	 * Note: we do not make a local lo_buf because we expect at most one BLOBS
	 * entry per archive, so no parallelism is possible.  Likewise,
	 * TOC-entry-local state isn't an issue because any one TOC entry is
	 * touched by just one worker child.
	 */
}