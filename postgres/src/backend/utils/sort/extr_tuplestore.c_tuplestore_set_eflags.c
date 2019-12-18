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
struct TYPE_5__ {scalar_t__ status; scalar_t__ memtupcount; int readptrcount; int eflags; TYPE_1__* readptrs; } ;
typedef  TYPE_2__ Tuplestorestate ;
struct TYPE_4__ {int eflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ TSS_INMEM ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
tuplestore_set_eflags(Tuplestorestate *state, int eflags)
{
	int			i;

	if (state->status != TSS_INMEM || state->memtupcount != 0)
		elog(ERROR, "too late to call tuplestore_set_eflags");

	state->readptrs[0].eflags = eflags;
	for (i = 1; i < state->readptrcount; i++)
		eflags |= state->readptrs[i].eflags;
	state->eflags = eflags;
}