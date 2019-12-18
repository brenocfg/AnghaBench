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
 int PG_SQL_ASCII ; 
 char* getenv (char*) ; 
 int pg_char_to_encoding (char*) ; 

int
PQenv2encoding(void)
{
	char	   *str;
	int			encoding = PG_SQL_ASCII;

	str = getenv("PGCLIENTENCODING");
	if (str && *str != '\0')
	{
		encoding = pg_char_to_encoding(str);
		if (encoding < 0)
			encoding = PG_SQL_ASCII;
	}
	return encoding;
}