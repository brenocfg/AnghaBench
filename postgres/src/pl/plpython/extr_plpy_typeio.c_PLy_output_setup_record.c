#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* TupleDesc ;
struct TYPE_11__ {TYPE_3__* recdesc; } ;
struct TYPE_12__ {TYPE_1__ tuple; } ;
struct TYPE_15__ {scalar_t__ typoid; TYPE_2__ u; int /*<<< orphan*/  typmod; } ;
struct TYPE_14__ {scalar_t__ tdtypeid; int /*<<< orphan*/  tdtypmod; } ;
struct TYPE_13__ {int /*<<< orphan*/  tdtypmod; } ;
typedef  int /*<<< orphan*/  PLyProcedure ;
typedef  TYPE_5__ PLyObToDatum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BlessTupleDesc (TYPE_4__*) ; 
 int /*<<< orphan*/  PLy_output_setup_tuple (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ RECORDOID ; 

void
PLy_output_setup_record(PLyObToDatum *arg, TupleDesc desc, PLyProcedure *proc)
{
	/* Makes no sense unless RECORD */
	Assert(arg->typoid == RECORDOID);
	Assert(desc->tdtypeid == RECORDOID);

	/*
	 * Bless the record type if not already done.  We'd have to do this anyway
	 * to return a tuple, so we might as well force the issue so we can use
	 * the known-record-type code path.
	 */
	BlessTupleDesc(desc);

	/*
	 * Update arg->typmod, and clear the recdesc link if it's changed. The
	 * next call of PLyObject_ToComposite will look up a long-lived tupdesc
	 * for the record type.
	 */
	arg->typmod = desc->tdtypmod;
	if (arg->u.tuple.recdesc &&
		arg->u.tuple.recdesc->tdtypmod != arg->typmod)
		arg->u.tuple.recdesc = NULL;

	/* Update derived data if necessary */
	PLy_output_setup_tuple(arg, desc, proc);
}