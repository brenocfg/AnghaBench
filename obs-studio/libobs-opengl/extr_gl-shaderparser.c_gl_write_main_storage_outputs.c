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
struct shader_var {char* name; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct shader_func {int /*<<< orphan*/  return_type; int /*<<< orphan*/  mapping; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gl_write_main_storage_assign (struct gl_shader_parser*,struct shader_var*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void gl_write_main_storage_outputs(struct gl_shader_parser *glsp,
						 struct shader_func *main)
{
	/* we only do this *if* we're writing a struct, because otherwise
	 * the call to 'main' already does the assignment for us */
	if (!main->mapping) {
		struct shader_var var = {0};
		var.name = "outputval";
		var.type = main->return_type;
		dstr_cat(&glsp->gl_string, "\n");
		gl_write_main_storage_assign(glsp, &var, NULL, NULL, false);
	}
}