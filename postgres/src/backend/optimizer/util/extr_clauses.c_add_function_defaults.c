#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pronargs; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fetch_function_defaults (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_copy_tail (int /*<<< orphan*/ *,int) ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
add_function_defaults(List *args, HeapTuple func_tuple)
{
	Form_pg_proc funcform = (Form_pg_proc) GETSTRUCT(func_tuple);
	int			nargsprovided = list_length(args);
	List	   *defaults;
	int			ndelete;

	/* Get all the default expressions from the pg_proc tuple */
	defaults = fetch_function_defaults(func_tuple);

	/* Delete any unused defaults from the list */
	ndelete = nargsprovided + list_length(defaults) - funcform->pronargs;
	if (ndelete < 0)
		elog(ERROR, "not enough default arguments");
	if (ndelete > 0)
		defaults = list_copy_tail(defaults, ndelete);

	/* And form the combined argument list, not modifying the input list */
	return list_concat_copy(args, defaults);
}