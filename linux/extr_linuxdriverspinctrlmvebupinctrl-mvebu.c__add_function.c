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
struct mvebu_pinctrl_function {int num_groups; char const* name; } ;

/* Variables and functions */
 int EEXIST ; 
 int EOVERFLOW ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int _add_function(struct mvebu_pinctrl_function *funcs, int *funcsize,
			const char *name)
{
	if (*funcsize <= 0)
		return -EOVERFLOW;

	while (funcs->num_groups) {
		/* function already there */
		if (strcmp(funcs->name, name) == 0) {
			funcs->num_groups++;
			return -EEXIST;
		}
		funcs++;
	}

	/* append new unique function */
	funcs->name = name;
	funcs->num_groups = 1;
	(*funcsize)--;

	return 0;
}