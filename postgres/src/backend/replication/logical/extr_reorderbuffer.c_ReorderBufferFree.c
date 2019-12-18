#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ ReorderBuffer ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 TYPE_4__* MyReplicationSlot ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferCleanupSerializedTXNs (int /*<<< orphan*/ ) ; 

void
ReorderBufferFree(ReorderBuffer *rb)
{
	MemoryContext context = rb->context;

	/*
	 * We free separately allocated data by entirely scrapping reorderbuffer's
	 * memory context.
	 */
	MemoryContextDelete(context);

	/* Free disk space used by unconsumed reorder buffers */
	ReorderBufferCleanupSerializedTXNs(NameStr(MyReplicationSlot->data.name));
}