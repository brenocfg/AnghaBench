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
struct shader_func {int dummy; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; int /*<<< orphan*/  parser; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gl_rename_attributes (struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_write_functions (struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_write_inputs (struct gl_shader_parser*,struct shader_func*) ; 
 int /*<<< orphan*/  gl_write_interface_block (struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_write_main (struct gl_shader_parser*,struct shader_func*) ; 
 int /*<<< orphan*/  gl_write_outputs (struct gl_shader_parser*,struct shader_func*) ; 
 int /*<<< orphan*/  gl_write_params (struct gl_shader_parser*) ; 
 int /*<<< orphan*/  gl_write_structs (struct gl_shader_parser*) ; 
 struct shader_func* shader_parser_getfunc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool gl_shader_buildstring(struct gl_shader_parser *glsp)
{
	struct shader_func *main_func;

	main_func = shader_parser_getfunc(&glsp->parser, "main");
	if (!main_func) {
		blog(LOG_ERROR, "function 'main' not found");
		return false;
	}

	dstr_copy(&glsp->gl_string, "#version 330\n\n");
	dstr_cat(&glsp->gl_string, "const bool obs_glsl_compile = true;\n\n");
	gl_write_params(glsp);
	gl_write_inputs(glsp, main_func);
	gl_write_outputs(glsp, main_func);
	gl_write_interface_block(glsp);
	gl_write_structs(glsp);
	gl_write_functions(glsp);
	gl_write_main(glsp, main_func);
	gl_rename_attributes(glsp);

	return true;
}