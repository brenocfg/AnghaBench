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
 char* pg_strdup (char*) ; 

__attribute__((used)) static char *
fetch_count_substitute_hook(char *newval)
{
	if (newval == NULL)
		newval = pg_strdup("0");
	return newval;
}