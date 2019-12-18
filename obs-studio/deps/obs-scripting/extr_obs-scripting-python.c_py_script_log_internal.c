#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {char* array; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 TYPE_1__ cur_py_log_chunk ; 
 TYPE_3__* cur_python_script ; 
 int /*<<< orphan*/  dstr_cat (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  dstr_resize (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int*,char const**) ; 
 int /*<<< orphan*/ * python_none () ; 
 int /*<<< orphan*/  script_log (int /*<<< orphan*/ *,int,char*,char const*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static PyObject *py_script_log_internal(PyObject *self, PyObject *args,
					bool add_endl)
{
	static bool calling_self = false;
	int log_level;
	const char *msg;

	UNUSED_PARAMETER(self);

	if (calling_self)
		return python_none();
	calling_self = true;

	/* ------------------- */

	if (!parse_args(args, "is", &log_level, &msg))
		goto fail;
	if (!msg || !*msg)
		goto fail;

	dstr_cat(&cur_py_log_chunk, msg);
	if (add_endl)
		dstr_cat(&cur_py_log_chunk, "\n");

	const char *start = cur_py_log_chunk.array;
	char *endl = strchr(start, '\n');

	while (endl) {
		*endl = 0;
		if (cur_python_script)
			script_log(&cur_python_script->base, log_level, "%s",
				   start);
		else
			script_log(NULL, log_level, "%s", start);
		*endl = '\n';

		start = endl + 1;
		endl = strchr(start, '\n');
	}

	if (start) {
		size_t len = strlen(start);
		if (len)
			memmove(cur_py_log_chunk.array, start, len);
		dstr_resize(&cur_py_log_chunk, len);
	}

	/* ------------------- */

fail:
	calling_self = false;
	return python_none();
}