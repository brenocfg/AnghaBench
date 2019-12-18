#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_2__ {int /*<<< orphan*/  minhdr; int /*<<< orphan*/ * tuple; } ;
typedef  TYPE_1__ MinimalTupleTableSlot ;

/* Variables and functions */

__attribute__((used)) static void
tts_minimal_init(TupleTableSlot *slot)
{
	MinimalTupleTableSlot *mslot = (MinimalTupleTableSlot *) slot;

	/*
	 * Initialize the heap tuple pointer to access attributes of the minimal
	 * tuple contained in the slot as if its a heap tuple.
	 */
	mslot->tuple = &mslot->minhdr;
}