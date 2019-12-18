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
typedef  int /*<<< orphan*/  deparse_namespace ;
typedef  int /*<<< orphan*/  deparse_columns ;

/* Variables and functions */
 scalar_t__ NAMEDATALEN ; 
 int /*<<< orphan*/  colname_is_unique (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ palloc (int) ; 
 int pg_mbcliplen (char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
make_colname_unique(char *colname, deparse_namespace *dpns,
					deparse_columns *colinfo)
{
	/*
	 * If the selected name isn't unique, append digits to make it so.  For a
	 * very long input name, we might have to truncate to stay within
	 * NAMEDATALEN.
	 */
	if (!colname_is_unique(colname, dpns, colinfo))
	{
		int			colnamelen = strlen(colname);
		char	   *modname = (char *) palloc(colnamelen + 16);
		int			i = 0;

		do
		{
			i++;
			for (;;)
			{
				/*
				 * We avoid using %.*s here because it can misbehave if the
				 * data is not valid in what libc thinks is the prevailing
				 * encoding.
				 */
				memcpy(modname, colname, colnamelen);
				sprintf(modname + colnamelen, "_%d", i);
				if (strlen(modname) < NAMEDATALEN)
					break;
				/* drop chars from colname to keep all the digits */
				colnamelen = pg_mbcliplen(colname, colnamelen,
										  colnamelen - 1);
			}
		} while (!colname_is_unique(modname, dpns, colinfo));
		colname = modname;
	}
	return colname;
}