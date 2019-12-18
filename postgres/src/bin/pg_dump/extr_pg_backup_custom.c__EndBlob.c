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
struct TYPE_6__ {int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ lclContext ;
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_7__ {scalar_t__ formatData; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  EndCompressor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteInt (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_EndBlob(ArchiveHandle *AH, TocEntry *te, Oid oid)
{
	lclContext *ctx = (lclContext *) AH->formatData;

	EndCompressor(AH, ctx->cs);
	/* Send the end marker */
	WriteInt(AH, 0);
}