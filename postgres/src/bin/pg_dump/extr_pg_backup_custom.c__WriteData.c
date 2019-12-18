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
struct TYPE_5__ {int /*<<< orphan*/ * cs; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_6__ {scalar_t__ formatData; } ;
typedef  int /*<<< orphan*/  CompressorState ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  WriteDataToArchive (TYPE_2__*,int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
_WriteData(ArchiveHandle *AH, const void *data, size_t dLen)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	CompressorState *cs = ctx->cs;

	if (dLen > 0)
		/* WriteDataToArchive() internally throws write errors */
		WriteDataToArchive(AH, cs, data, dLen);

	return;
}