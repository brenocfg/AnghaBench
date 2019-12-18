#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; struct shader_func* array; } ;
struct shader_parser {TYPE_1__ funcs; } ;
struct shader_func {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline struct shader_func *
shader_parser_getfunc(struct shader_parser *sp, const char *func_name)
{
	size_t i;
	for (i = 0; i < sp->funcs.num; i++) {
		struct shader_func *func = sp->funcs.array + i;
		if (strcmp(func->name, func_name) == 0)
			return func;
	}

	return NULL;
}