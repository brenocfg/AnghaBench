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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *change_name(char *name, char *orig_name, int dup)
{
	char *new_name = NULL;
	size_t len;

	if (!name)
		name = orig_name;

	if (dup >= 10)
		goto out;
	/*
	 * Add '_' prefix to potential keywork.  According to
	 * Mathieu Desnoyers (https://lkml.org/lkml/2015/1/23/652),
	 * futher CTF spec updating may require us to use '$'.
	 */
	if (dup < 0)
		len = strlen(name) + sizeof("_");
	else
		len = strlen(orig_name) + sizeof("_dupl_X");

	new_name = malloc(len);
	if (!new_name)
		goto out;

	if (dup < 0)
		snprintf(new_name, len, "_%s", name);
	else
		snprintf(new_name, len, "%s_dupl_%d", orig_name, dup);

out:
	if (name != orig_name)
		free(name);
	return new_name;
}