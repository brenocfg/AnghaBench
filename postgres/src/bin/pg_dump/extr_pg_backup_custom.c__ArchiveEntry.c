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
struct TYPE_4__ {int /*<<< orphan*/  dataState; } ;
typedef  TYPE_1__ lclTocEntry ;
struct TYPE_5__ {void* formatData; scalar_t__ dataDumper; } ;
typedef  TYPE_2__ TocEntry ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  K_OFFSET_NO_DATA ; 
 int /*<<< orphan*/  K_OFFSET_POS_NOT_SET ; 
 scalar_t__ pg_malloc0 (int) ; 

__attribute__((used)) static void
_ArchiveEntry(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *ctx;

	ctx = (lclTocEntry *) pg_malloc0(sizeof(lclTocEntry));
	if (te->dataDumper)
		ctx->dataState = K_OFFSET_POS_NOT_SET;
	else
		ctx->dataState = K_OFFSET_NO_DATA;

	te->formatData = (void *) ctx;
}