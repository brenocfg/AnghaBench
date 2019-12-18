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
 char* initial_path ; 
 scalar_t__ initial_pathlen ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 

__attribute__((used)) static void set_initial_path(char *fname)
{
	int i, len = strlen(fname);

	xasprintf(&initial_path, "%s", fname);
	initial_pathlen = 0;
	for (i = 0; i != len; i++)
		if (initial_path[i] == '/')
			initial_pathlen++;
}