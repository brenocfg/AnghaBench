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
 int deferred_skip_index ; 
 int /*<<< orphan*/ * deferred_skip_names ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

int is_deferred_skip(char *name)
{
	int i;

	for (i = 0; i < deferred_skip_index; ++i)
		if (!strcmp(name, deferred_skip_names[i]))
			return 1;
	return 0;
}