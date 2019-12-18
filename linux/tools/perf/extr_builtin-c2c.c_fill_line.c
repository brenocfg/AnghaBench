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
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* zalloc (int) ; 

__attribute__((used)) static char *fill_line(const char *orig, int len)
{
	int i, j, olen = strlen(orig);
	char *buf;

	buf = zalloc(len + 1);
	if (!buf)
		return NULL;

	j = len / 2 - olen / 2;

	for (i = 0; i < j - 1; i++)
		buf[i] = '-';

	buf[i++] = ' ';

	strcpy(buf + i, orig);

	i += olen;

	buf[i++] = ' ';

	for (; i < len; i++)
		buf[i] = '-';

	return buf;
}