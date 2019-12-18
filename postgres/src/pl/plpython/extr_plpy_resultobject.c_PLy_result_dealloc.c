#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * tupdesc; int /*<<< orphan*/  status; int /*<<< orphan*/  rows; int /*<<< orphan*/  nrows; } ;
struct TYPE_7__ {TYPE_1__* ob_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* tp_free ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ PyObject ;
typedef  TYPE_3__ PLyResultObject ;

/* Variables and functions */
 int /*<<< orphan*/  FreeTupleDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
PLy_result_dealloc(PyObject *arg)
{
	PLyResultObject *ob = (PLyResultObject *) arg;

	Py_XDECREF(ob->nrows);
	Py_XDECREF(ob->rows);
	Py_XDECREF(ob->status);
	if (ob->tupdesc)
	{
		FreeTupleDesc(ob->tupdesc);
		ob->tupdesc = NULL;
	}

	arg->ob_type->tp_free(arg);
}