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
struct TYPE_4__ {int /*<<< orphan*/  readtup; int /*<<< orphan*/  writetup; int /*<<< orphan*/  copytup; } ;
typedef  TYPE_1__ Tuplestorestate ;

/* Variables and functions */
 int EXEC_FLAG_BACKWARD ; 
 int EXEC_FLAG_REWIND ; 
 int /*<<< orphan*/  copytup_heap ; 
 int /*<<< orphan*/  readtup_heap ; 
 TYPE_1__* tuplestore_begin_common (int,int,int) ; 
 int /*<<< orphan*/  writetup_heap ; 

Tuplestorestate *
tuplestore_begin_heap(bool randomAccess, bool interXact, int maxKBytes)
{
	Tuplestorestate *state;
	int			eflags;

	/*
	 * This interpretation of the meaning of randomAccess is compatible with
	 * the pre-8.3 behavior of tuplestores.
	 */
	eflags = randomAccess ?
		(EXEC_FLAG_BACKWARD | EXEC_FLAG_REWIND) :
		(EXEC_FLAG_REWIND);

	state = tuplestore_begin_common(eflags, interXact, maxKBytes);

	state->copytup = copytup_heap;
	state->writetup = writetup_heap;
	state->readtup = readtup_heap;

	return state;
}