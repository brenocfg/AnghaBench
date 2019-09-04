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
typedef  scalar_t__ char_u ;
struct TYPE_3__ {int /*<<< orphan*/  opt_type; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ OptionsObject ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__* StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ get_option_value_strict (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
OptionsContains(OptionsObject *self, PyObject *keyObject)
{
    char_u	*key;
    PyObject	*todecref;

    if (!(key = StringToChars(keyObject, &todecref)))
	return -1;

    if (*key == NUL)
    {
	Py_XDECREF(todecref);
	return 0;
    }

    if (get_option_value_strict(key, NULL, NULL, self->opt_type, NULL))
    {
	Py_XDECREF(todecref);
	return 1;
    }
    else
    {
	Py_XDECREF(todecref);
	return 0;
    }
}