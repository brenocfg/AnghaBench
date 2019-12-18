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
struct TYPE_2__ {int /*<<< orphan*/  encoding; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQfname (int /*<<< orphan*/  const*,int) ; 
 int PQnfields (int /*<<< orphan*/  const*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  dequote_downcase_identifier (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 TYPE_1__ pset ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 

__attribute__((used)) static int
indexOfColumn(char *arg, const PGresult *res)
{
	int			idx;

	if (arg[0] && strspn(arg, "0123456789") == strlen(arg))
	{
		/* if arg contains only digits, it's a column number */
		idx = atoi(arg) - 1;
		if (idx < 0 || idx >= PQnfields(res))
		{
			pg_log_error("\\crosstabview: column number %d is out of range 1..%d",
						 idx + 1, PQnfields(res));
			return -1;
		}
	}
	else
	{
		int			i;

		/*
		 * Dequote and downcase the column name.  By checking for all-digits
		 * before doing this, we can ensure that a quoted name is treated as a
		 * name even if it's all digits.
		 */
		dequote_downcase_identifier(arg, true, pset.encoding);

		/* Now look for match(es) among res' column names */
		idx = -1;
		for (i = 0; i < PQnfields(res); i++)
		{
			if (strcmp(arg, PQfname(res, i)) == 0)
			{
				if (idx >= 0)
				{
					/* another idx was already found for the same name */
					pg_log_error("\\crosstabview: ambiguous column name: \"%s\"", arg);
					return -1;
				}
				idx = i;
			}
		}
		if (idx == -1)
		{
			pg_log_error("\\crosstabview: column name not found: \"%s\"", arg);
			return -1;
		}
	}

	return idx;
}