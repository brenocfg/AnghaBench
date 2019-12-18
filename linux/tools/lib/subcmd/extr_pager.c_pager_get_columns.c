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
 int atoi (char*) ; 
 char* getenv (char*) ; 
 int pager_columns ; 

int pager_get_columns(void)
{
	char *s;

	s = getenv("COLUMNS");
	if (s)
		return atoi(s);

	return (pager_columns ? pager_columns : 80) - 2;
}