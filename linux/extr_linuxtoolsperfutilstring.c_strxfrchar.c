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
 char* strchr (char*,char) ; 

char *strxfrchar(char *s, char from, char to)
{
	char *p = s;

	while ((p = strchr(p, from)) != NULL)
		*p++ = to;

	return s;
}