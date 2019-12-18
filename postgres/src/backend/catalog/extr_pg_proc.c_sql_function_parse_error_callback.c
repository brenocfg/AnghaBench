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
struct TYPE_2__ {int /*<<< orphan*/  proname; int /*<<< orphan*/  prosrc; } ;
typedef  TYPE_1__ parse_error_callback_arg ;

/* Variables and functions */
 int /*<<< orphan*/  errcontext (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  function_parse_error_transpose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sql_function_parse_error_callback(void *arg)
{
	parse_error_callback_arg *callback_arg = (parse_error_callback_arg *) arg;

	/* See if it's a syntax error; if so, transpose to CREATE FUNCTION */
	if (!function_parse_error_transpose(callback_arg->prosrc))
	{
		/* If it's not a syntax error, push info onto context stack */
		errcontext("SQL function \"%s\"", callback_arg->proname);
	}
}