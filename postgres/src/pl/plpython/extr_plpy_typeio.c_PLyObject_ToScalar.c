#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  typioparam; int /*<<< orphan*/  typfunc; } ;
struct TYPE_6__ {TYPE_1__ scalar; } ;
struct TYPE_7__ {int /*<<< orphan*/  typmod; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ PLyObToDatum ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  InputFunctionCall (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* PLyObject_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static Datum
PLyObject_ToScalar(PLyObToDatum *arg, PyObject *plrv,
				   bool *isnull, bool inarray)
{
	char	   *str;

	if (plrv == Py_None)
	{
		*isnull = true;
		return (Datum) 0;
	}
	*isnull = false;

	str = PLyObject_AsString(plrv);

	return InputFunctionCall(&arg->u.scalar.typfunc,
							 str,
							 arg->u.scalar.typioparam,
							 arg->typmod);
}