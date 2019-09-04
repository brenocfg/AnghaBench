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
struct function {int min_args; int max_args; char* (* func ) (int,char**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct function*) ; 
 struct function* function_table ; 
 int /*<<< orphan*/  pperror (char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* stub1 (int,char**) ; 

__attribute__((used)) static char *function_expand(const char *name, int argc, char *argv[])
{
	const struct function *f;
	int i;

	for (i = 0; i < ARRAY_SIZE(function_table); i++) {
		f = &function_table[i];
		if (strcmp(f->name, name))
			continue;

		if (argc < f->min_args)
			pperror("too few function arguments passed to '%s'",
				name);

		if (argc > f->max_args)
			pperror("too many function arguments passed to '%s'",
				name);

		return f->func(argc, argv);
	}

	return NULL;
}