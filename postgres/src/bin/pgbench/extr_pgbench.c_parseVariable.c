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
 scalar_t__ IS_HIGHBIT_SET (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* pg_malloc (int) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 

__attribute__((used)) static char *
parseVariable(const char *sql, int *eaten)
{
	int			i = 0;
	char	   *name;

	do
	{
		i++;
	} while (IS_HIGHBIT_SET(sql[i]) ||
			 strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz"
					"_0123456789", sql[i]) != NULL);
	if (i == 1)
		return NULL;			/* no valid variable name chars */

	name = pg_malloc(i);
	memcpy(name, &sql[1], i - 1);
	name[i - 1] = '\0';

	*eaten = i;
	return name;
}