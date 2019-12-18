#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {scalar_t__ nused; int /*<<< orphan*/  bistate; int /*<<< orphan*/ * resultRelInfo; int /*<<< orphan*/  slots; } ;
typedef  int /*<<< orphan*/  ResultRelInfo ;
typedef  TYPE_1__ CopyMultiInsertBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GetBulkInsertState () ; 
 int MAX_BUFFERED_TUPLES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static CopyMultiInsertBuffer *
CopyMultiInsertBufferInit(ResultRelInfo *rri)
{
	CopyMultiInsertBuffer *buffer;

	buffer = (CopyMultiInsertBuffer *) palloc(sizeof(CopyMultiInsertBuffer));
	memset(buffer->slots, 0, sizeof(TupleTableSlot *) * MAX_BUFFERED_TUPLES);
	buffer->resultRelInfo = rri;
	buffer->bistate = GetBulkInsertState();
	buffer->nused = 0;

	return buffer;
}