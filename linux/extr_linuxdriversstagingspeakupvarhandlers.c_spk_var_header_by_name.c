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
struct st_var_header {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAXVARS ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct st_var_header** var_ptrs ; 

struct st_var_header *spk_var_header_by_name(const char *name)
{
	int i;

	if (!name)
		return NULL;

	for (i = 0; i < MAXVARS; i++) {
		if (strcmp(name, var_ptrs[i]->name) == 0)
			return var_ptrs[i];
	}
	return NULL;
}