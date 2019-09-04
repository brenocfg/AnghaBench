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
struct tables {int /*<<< orphan*/  dbe; } ;

/* Variables and functions */
 int /*<<< orphan*/  Py_Finalize () ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_export__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_dict ; 
 int /*<<< orphan*/  main_module ; 
 struct tables tables_global ; 
 int /*<<< orphan*/  try_call_object (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int python_stop_script(void)
{
	struct tables *tables = &tables_global;

	try_call_object("trace_end", NULL);

	db_export__exit(&tables->dbe);

	Py_XDECREF(main_dict);
	Py_XDECREF(main_module);
	Py_Finalize();

	return 0;
}