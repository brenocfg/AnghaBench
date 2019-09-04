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
 scalar_t__ isspace (char) ; 
 int strlen (char*) ; 

__attribute__((used)) static void fixdesc(char *s)
{
	char *e = s + strlen(s);

	/* Remove trailing dots that look ugly in perf list */
	--e;
	while (e >= s && isspace(*e))
		--e;
	if (*e == '.')
		*e = 0;
}