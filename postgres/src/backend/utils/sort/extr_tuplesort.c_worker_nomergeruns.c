#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int result_tape; int* tp_tapenum; size_t destTape; } ;
typedef  TYPE_1__ Tuplesortstate ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int WORKER (TYPE_1__*) ; 
 int /*<<< orphan*/  worker_freeze_result_tape (TYPE_1__*) ; 

__attribute__((used)) static void
worker_nomergeruns(Tuplesortstate *state)
{
	Assert(WORKER(state));
	Assert(state->result_tape == -1);

	state->result_tape = state->tp_tapenum[state->destTape];
	worker_freeze_result_tape(state);
}