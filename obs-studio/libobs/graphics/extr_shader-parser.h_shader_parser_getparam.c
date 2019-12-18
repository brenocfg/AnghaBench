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
struct shader_var {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {size_t num; struct shader_var* array; } ;
struct shader_parser {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline struct shader_var *
shader_parser_getparam(struct shader_parser *sp, const char *param_name)
{
	size_t i;
	for (i = 0; i < sp->params.num; i++) {
		struct shader_var *param = sp->params.array + i;
		if (strcmp(param->name, param_name) == 0)
			return param;
	}

	return NULL;
}