#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sqlstate; int /*<<< orphan*/  classname; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * exc; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyExceptionEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/ * PLy_create_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PLy_spi_exceptions ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 TYPE_3__* exception_map ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  unpack_sql_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PLy_generate_spi_exceptions(PyObject *mod, PyObject *base)
{
	int			i;

	for (i = 0; exception_map[i].name != NULL; i++)
	{
		bool		found;
		PyObject   *exc;
		PLyExceptionEntry *entry;
		PyObject   *sqlstate;
		PyObject   *dict = PyDict_New();

		if (dict == NULL)
			PLy_elog(ERROR, NULL);

		sqlstate = PyString_FromString(unpack_sql_state(exception_map[i].sqlstate));
		if (sqlstate == NULL)
			PLy_elog(ERROR, "could not generate SPI exceptions");

		PyDict_SetItemString(dict, "sqlstate", sqlstate);
		Py_DECREF(sqlstate);

		exc = PLy_create_exception(exception_map[i].name, base, dict,
								   exception_map[i].classname, mod);

		entry = hash_search(PLy_spi_exceptions, &exception_map[i].sqlstate,
							HASH_ENTER, &found);
		Assert(!found);
		entry->exc = exc;
	}
}