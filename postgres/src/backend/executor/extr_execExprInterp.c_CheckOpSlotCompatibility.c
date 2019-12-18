#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * tts_ops; } ;
typedef  TYPE_3__ TupleTableSlot ;
struct TYPE_7__ {int /*<<< orphan*/ * kind; int /*<<< orphan*/  fixed; } ;
struct TYPE_8__ {TYPE_1__ fetch; } ;
struct TYPE_10__ {TYPE_2__ d; } ;
typedef  TYPE_4__ ExprEvalStep ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTSOpsBufferHeapTuple ; 
 int /*<<< orphan*/  TTSOpsHeapTuple ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 

__attribute__((used)) static void
CheckOpSlotCompatibility(ExprEvalStep *op, TupleTableSlot *slot)
{
#ifdef USE_ASSERT_CHECKING
	/* there's nothing to check */
	if (!op->d.fetch.fixed)
		return;

	/*
	 * Should probably fixed at some point, but for now it's easier to allow
	 * buffer and heap tuples to be used interchangeably.
	 */
	if (slot->tts_ops == &TTSOpsBufferHeapTuple &&
		op->d.fetch.kind == &TTSOpsHeapTuple)
		return;
	if (slot->tts_ops == &TTSOpsHeapTuple &&
		op->d.fetch.kind == &TTSOpsBufferHeapTuple)
		return;

	/*
	 * At the moment we consider it OK if a virtual slot is used instead of a
	 * specific type of slot, as a virtual slot never needs to be deformed.
	 */
	if (slot->tts_ops == &TTSOpsVirtual)
		return;

	Assert(op->d.fetch.kind == slot->tts_ops);
#endif
}