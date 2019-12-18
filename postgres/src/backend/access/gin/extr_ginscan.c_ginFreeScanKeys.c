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
typedef  size_t uint32 ;
struct TYPE_5__ {scalar_t__ buffer; scalar_t__ matchBitmap; scalar_t__ matchIterator; scalar_t__ list; } ;
struct TYPE_4__ {size_t totalentries; TYPE_2__** entries; scalar_t__ nkeys; int /*<<< orphan*/ * keys; int /*<<< orphan*/  keyCtx; } ;
typedef  TYPE_1__* GinScanOpaque ;
typedef  TYPE_2__* GinScanEntry ;

/* Variables and functions */
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 
 int /*<<< orphan*/  tbm_end_iterate (scalar_t__) ; 
 int /*<<< orphan*/  tbm_free (scalar_t__) ; 

void
ginFreeScanKeys(GinScanOpaque so)
{
	uint32		i;

	if (so->keys == NULL)
		return;

	for (i = 0; i < so->totalentries; i++)
	{
		GinScanEntry entry = so->entries[i];

		if (entry->buffer != InvalidBuffer)
			ReleaseBuffer(entry->buffer);
		if (entry->list)
			pfree(entry->list);
		if (entry->matchIterator)
			tbm_end_iterate(entry->matchIterator);
		if (entry->matchBitmap)
			tbm_free(entry->matchBitmap);
	}

	MemoryContextResetAndDeleteChildren(so->keyCtx);

	so->keys = NULL;
	so->nkeys = 0;
	so->entries = NULL;
	so->totalentries = 0;
}