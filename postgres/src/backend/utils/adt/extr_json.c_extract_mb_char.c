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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* palloc (int) ; 
 int pg_mblen (char*) ; 

__attribute__((used)) static char *
extract_mb_char(char *s)
{
	char	   *res;
	int			len;

	len = pg_mblen(s);
	res = palloc(len + 1);
	memcpy(res, s, len);
	res[len] = '\0';

	return res;
}