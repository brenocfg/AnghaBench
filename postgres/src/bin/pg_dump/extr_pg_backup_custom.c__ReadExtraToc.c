#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dataPos; int /*<<< orphan*/  dataState; } ;
typedef  TYPE_1__ lclTocEntry ;
struct TYPE_9__ {void* formatData; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_10__ {scalar_t__ version; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ K_VERS_1_7 ; 
 int /*<<< orphan*/  ReadInt (TYPE_3__*) ; 
 int /*<<< orphan*/  ReadOffset (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ pg_malloc0 (int) ; 

__attribute__((used)) static void
_ReadExtraToc(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *ctx = (lclTocEntry *) te->formatData;

	if (ctx == NULL)
	{
		ctx = (lclTocEntry *) pg_malloc0(sizeof(lclTocEntry));
		te->formatData = (void *) ctx;
	}

	ctx->dataState = ReadOffset(AH, &(ctx->dataPos));

	/*
	 * Prior to V1.7 (pg7.3), we dumped the data size as an int now we don't
	 * dump it at all.
	 */
	if (AH->version < K_VERS_1_7)
		ReadInt(AH);
}