#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  TH; } ;
typedef  TYPE_2__ lclTocEntry ;
struct TYPE_7__ {TYPE_1__* currToc; } ;
struct TYPE_5__ {scalar_t__ formatData; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ERROR_EXIT ; 
 size_t tarWrite (void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_WriteData(ArchiveHandle *AH, const void *data, size_t dLen)
{
	lclTocEntry *tctx = (lclTocEntry *) AH->currToc->formatData;

	if (tarWrite(data, dLen, tctx->TH) != dLen)
		WRITE_ERROR_EXIT;

	return;
}