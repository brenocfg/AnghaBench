#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num; TYPE_1__* array; } ;
struct shader_func {char* return_type; int /*<<< orphan*/  mapping; TYPE_2__ params; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; } ;
struct TYPE_3__ {char* type; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline void gl_write_main_vars(struct gl_shader_parser *glsp,
				      struct shader_func *main_func)
{
	size_t i;
	for (i = 0; i < main_func->params.num; i++) {
		dstr_cat(&glsp->gl_string, "\t");
		dstr_cat(&glsp->gl_string, main_func->params.array[i].type);
		dstr_cat(&glsp->gl_string, " ");
		dstr_cat(&glsp->gl_string, main_func->params.array[i].name);
		dstr_cat(&glsp->gl_string, ";\n");
	}

	if (!main_func->mapping) {
		dstr_cat(&glsp->gl_string, "\t");
		dstr_cat(&glsp->gl_string, main_func->return_type);
		dstr_cat(&glsp->gl_string, " outputval;\n\n");
	}
}