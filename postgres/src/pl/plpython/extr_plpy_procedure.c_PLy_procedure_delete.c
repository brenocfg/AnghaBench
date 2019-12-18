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
struct TYPE_3__ {int /*<<< orphan*/  mcxt; int /*<<< orphan*/  globals; int /*<<< orphan*/  statics; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ PLyProcedure ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 

void
PLy_procedure_delete(PLyProcedure *proc)
{
	Py_XDECREF(proc->code);
	Py_XDECREF(proc->statics);
	Py_XDECREF(proc->globals);
	MemoryContextDelete(proc->mcxt);
}