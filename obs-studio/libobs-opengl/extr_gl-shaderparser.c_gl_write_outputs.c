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
struct shader_var {char* name; scalar_t__ mapping; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct shader_func {scalar_t__ mapping; int /*<<< orphan*/  return_type; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gl_write_storage_var (struct gl_shader_parser*,struct shader_var*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_write_outputs(struct gl_shader_parser *glsp,
			     struct shader_func *main)
{
	struct shader_var var = {0};
	var.type = main->return_type;
	var.name = "outputval";
	if (main->mapping)
		var.mapping = main->mapping;

	gl_write_storage_var(glsp, &var, false, NULL);
	dstr_cat(&glsp->gl_string, "\n");
}