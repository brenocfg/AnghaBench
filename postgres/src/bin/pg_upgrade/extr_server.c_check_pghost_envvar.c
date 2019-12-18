#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* envvar; int /*<<< orphan*/ * keyword; } ;
typedef  TYPE_1__ PQconninfoOption ;

/* Variables and functions */
 TYPE_1__* PQconndefaults () ; 
 int /*<<< orphan*/  PQconninfoFree (TYPE_1__*) ; 
 char* getenv (char const*) ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

void
check_pghost_envvar(void)
{
	PQconninfoOption *option;
	PQconninfoOption *start;

	/* Get valid libpq env vars from the PQconndefaults function */

	start = PQconndefaults();

	if (!start)
		pg_fatal("out of memory\n");

	for (option = start; option->keyword != NULL; option++)
	{
		if (option->envvar && (strcmp(option->envvar, "PGHOST") == 0 ||
							   strcmp(option->envvar, "PGHOSTADDR") == 0))
		{
			const char *value = getenv(option->envvar);

			if (value && strlen(value) > 0 &&
			/* check for 'local' host values */
				(strcmp(value, "localhost") != 0 && strcmp(value, "127.0.0.1") != 0 &&
				 strcmp(value, "::1") != 0 && value[0] != '/'))
				pg_fatal("libpq environment variable %s has a non-local server value: %s\n",
						 option->envvar, value);
		}
	}

	/* Free the memory that libpq allocated on our behalf */
	PQconninfoFree(start);
}