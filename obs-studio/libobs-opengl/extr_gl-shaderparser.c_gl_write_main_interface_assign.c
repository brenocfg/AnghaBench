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
struct shader_var {char* name; int /*<<< orphan*/  mapping; } ;
struct gl_shader_parser {scalar_t__ type; int /*<<< orphan*/  gl_string; } ;

/* Variables and functions */
 scalar_t__ GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void gl_write_main_interface_assign(struct gl_shader_parser *glsp,
						  struct shader_var *var,
						  const char *src)
{
	/* vertex shaders: write gl_Position */
	if (glsp->type == GS_SHADER_VERTEX &&
	    strcmp(var->mapping, "POSITION") == 0) {
		dstr_cat(&glsp->gl_string, "\tgl_Position = ");
		dstr_cat(&glsp->gl_string, src);
		dstr_cat(&glsp->gl_string, var->name);
		dstr_cat(&glsp->gl_string, ";\n");
	}
}