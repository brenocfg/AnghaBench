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

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NAME_TOO_LONG ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int pg_mbcliplen (char*,int,int) ; 

void
truncate_identifier(char *ident, int len, bool warn)
{
	if (len >= NAMEDATALEN)
	{
		len = pg_mbcliplen(ident, len, NAMEDATALEN - 1);
		if (warn)
		{
			/*
			 * We avoid using %.*s here because it can misbehave if the data
			 * is not valid in what libc thinks is the prevailing encoding.
			 */
			char		buf[NAMEDATALEN];

			memcpy(buf, ident, len);
			buf[len] = '\0';
			ereport(NOTICE,
					(errcode(ERRCODE_NAME_TOO_LONG),
					 errmsg("identifier \"%s\" will be truncated to \"%s\"",
							ident, buf)));
		}
		ident[len] = '\0';
	}
}