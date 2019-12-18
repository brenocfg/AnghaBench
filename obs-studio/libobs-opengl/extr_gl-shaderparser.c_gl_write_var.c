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
struct shader_var {scalar_t__ var_type; char* name; int /*<<< orphan*/  type; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; } ;

/* Variables and functions */
 scalar_t__ SHADER_VAR_CONST ; 
 scalar_t__ SHADER_VAR_INOUT ; 
 scalar_t__ SHADER_VAR_OUT ; 
 scalar_t__ SHADER_VAR_UNIFORM ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gl_write_type (struct gl_shader_parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_write_var(struct gl_shader_parser *glsp, struct shader_var *var)
{
	if (var->var_type == SHADER_VAR_UNIFORM)
		dstr_cat(&glsp->gl_string, "uniform ");
	else if (var->var_type == SHADER_VAR_CONST)
		dstr_cat(&glsp->gl_string, "const ");
	else if (var->var_type == SHADER_VAR_INOUT)
		dstr_cat(&glsp->gl_string, "inout ");
	else if (var->var_type == SHADER_VAR_OUT)
		dstr_cat(&glsp->gl_string, "out ");

	gl_write_type(glsp, var->type);
	dstr_cat(&glsp->gl_string, " ");
	dstr_cat(&glsp->gl_string, var->name);
}