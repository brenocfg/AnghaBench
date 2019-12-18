#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_8__ {size_t nused; int /*<<< orphan*/ * linenos; int /*<<< orphan*/ ** slots; } ;
struct TYPE_7__ {int bufferedBytes; int /*<<< orphan*/  bufferedTuples; } ;
struct TYPE_6__ {TYPE_3__* ri_CopyMultiInsertBuffer; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  TYPE_2__ CopyMultiInsertInfo ;
typedef  TYPE_3__ CopyMultiInsertBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static inline void
CopyMultiInsertInfoStore(CopyMultiInsertInfo *miinfo, ResultRelInfo *rri,
						 TupleTableSlot *slot, int tuplen, uint64 lineno)
{
	CopyMultiInsertBuffer *buffer = rri->ri_CopyMultiInsertBuffer;

	Assert(buffer != NULL);
	Assert(slot == buffer->slots[buffer->nused]);

	/* Store the line number so we can properly report any errors later */
	buffer->linenos[buffer->nused] = lineno;

	/* Record this slot as being used */
	buffer->nused++;

	/* Update how many tuples are stored and their size */
	miinfo->bufferedTuples++;
	miinfo->bufferedBytes += tuplen;
}