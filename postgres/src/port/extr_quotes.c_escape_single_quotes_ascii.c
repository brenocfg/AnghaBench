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
 scalar_t__ SQL_STR_DOUBLE (char const,int) ; 
 char* malloc (int) ; 
 int strlen (char const*) ; 

char *
escape_single_quotes_ascii(const char *src)
{
	int			len = strlen(src),
				i,
				j;
	char	   *result = malloc(len * 2 + 1);

	if (!result)
		return NULL;

	for (i = 0, j = 0; i < len; i++)
	{
		if (SQL_STR_DOUBLE(src[i], true))
			result[j++] = src[i];
		result[j++] = src[i];
	}
	result[j] = '\0';
	return result;
}