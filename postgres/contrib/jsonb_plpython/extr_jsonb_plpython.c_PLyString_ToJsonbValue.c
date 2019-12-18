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
struct TYPE_5__ {int /*<<< orphan*/  val; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {TYPE_1__ string; } ;
struct TYPE_7__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ JsonbValue ;

/* Variables and functions */
 int /*<<< orphan*/  PLyObject_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbvString ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PLyString_ToJsonbValue(PyObject *obj, JsonbValue *jbvElem)
{
	jbvElem->type = jbvString;
	jbvElem->val.string.val = PLyObject_AsString(obj);
	jbvElem->val.string.len = strlen(jbvElem->val.string.val);
}