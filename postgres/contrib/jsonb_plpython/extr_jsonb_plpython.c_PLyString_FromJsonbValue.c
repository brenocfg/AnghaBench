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
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_6__ {TYPE_1__ string; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ JsonbValue ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * PyString_FromStringAndSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jbvString ; 

__attribute__((used)) static PyObject *
PLyString_FromJsonbValue(JsonbValue *jbv)
{
	Assert(jbv->type == jbvString);

	return PyString_FromStringAndSize(jbv->val.string.val, jbv->val.string.len);
}