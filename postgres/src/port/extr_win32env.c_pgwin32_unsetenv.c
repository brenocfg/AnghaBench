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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  pgwin32_putenv (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void
pgwin32_unsetenv(const char *name)
{
	char	   *envbuf;

	envbuf = (char *) malloc(strlen(name) + 2);
	if (!envbuf)
		return;

	sprintf(envbuf, "%s=", name);
	pgwin32_putenv(envbuf);
	free(envbuf);
}