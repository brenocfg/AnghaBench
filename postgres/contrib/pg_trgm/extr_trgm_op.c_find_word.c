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
 scalar_t__ ISWORDCHR (char*) ; 
 int /*<<< orphan*/  pg_mblen (char*) ; 

__attribute__((used)) static char *
find_word(char *str, int lenstr, char **endword, int *charlen)
{
	char	   *beginword = str;

	while (beginword - str < lenstr && !ISWORDCHR(beginword))
		beginword += pg_mblen(beginword);

	if (beginword - str >= lenstr)
		return NULL;

	*endword = beginword;
	*charlen = 0;
	while (*endword - str < lenstr && ISWORDCHR(*endword))
	{
		*endword += pg_mblen(*endword);
		(*charlen)++;
	}

	return beginword;
}