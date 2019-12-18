#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nentries_mem; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ReorderBufferSerializeTXN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ max_changes_in_memory ; 

__attribute__((used)) static void
ReorderBufferCheckSerializeTXN(ReorderBuffer *rb, ReorderBufferTXN *txn)
{
	/*
	 * TODO: improve accounting so we cheaply can take subtransactions into
	 * account here.
	 */
	if (txn->nentries_mem >= max_changes_in_memory)
	{
		ReorderBufferSerializeTXN(rb, txn);
		Assert(txn->nentries_mem == 0);
	}
}