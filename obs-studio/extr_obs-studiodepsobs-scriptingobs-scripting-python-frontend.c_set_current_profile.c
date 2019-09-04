#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_frontend_set_current_profile (char const*) ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/ * python_none () ; 

__attribute__((used)) static PyObject *set_current_profile(PyObject *self, PyObject *args)
{
	const char *name;
	if (!parse_args(args, "s", &name))
		return python_none();

	UNUSED_PARAMETER(self);

	obs_frontend_set_current_profile(name);
	return python_none();
}