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
 char* palloc (int) ; 
 int quote_literal_internal (char*,char const*,int) ; 
 int strlen (char const*) ; 

char *
quote_literal_cstr(const char *rawstr)
{
	char	   *result;
	int			len;
	int			newlen;

	len = strlen(rawstr);
	/* We make a worst-case result area; wasting a little space is OK */
	result = palloc(len * 2 + 3 + 1);

	newlen = quote_literal_internal(result, rawstr, len);
	result[newlen] = '\0';

	return result;
}