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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  PLpgSQL_datum ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/ * cstring_to_text (char const*) ; 
 int /*<<< orphan*/  exec_assign_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_eval_mcontext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
exec_assign_c_string(PLpgSQL_execstate *estate, PLpgSQL_datum *target,
					 const char *str)
{
	text	   *value;
	MemoryContext oldcontext;

	/* Use eval_mcontext for short-lived text value */
	oldcontext = MemoryContextSwitchTo(get_eval_mcontext(estate));
	if (str != NULL)
		value = cstring_to_text(str);
	else
		value = cstring_to_text("");
	MemoryContextSwitchTo(oldcontext);

	exec_assign_value(estate, target, PointerGetDatum(value), false,
					  TEXTOID, -1);
}