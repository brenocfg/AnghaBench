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
struct TYPE_2__ {scalar_t__ tablename; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ import_error_callback_arg ;

/* Variables and functions */
 int /*<<< orphan*/  errcontext (char*,scalar_t__) ; 
 int /*<<< orphan*/  errposition (int /*<<< orphan*/ ) ; 
 int geterrposition () ; 
 int /*<<< orphan*/  internalerrposition (int) ; 
 int /*<<< orphan*/  internalerrquery (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
import_error_callback(void *arg)
{
	import_error_callback_arg *callback_arg = (import_error_callback_arg *) arg;
	int			syntaxerrposition;

	/* If it's a syntax error, convert to internal syntax error report */
	syntaxerrposition = geterrposition();
	if (syntaxerrposition > 0)
	{
		errposition(0);
		internalerrposition(syntaxerrposition);
		internalerrquery(callback_arg->cmd);
	}

	if (callback_arg->tablename)
		errcontext("importing foreign table \"%s\"",
				   callback_arg->tablename);
}