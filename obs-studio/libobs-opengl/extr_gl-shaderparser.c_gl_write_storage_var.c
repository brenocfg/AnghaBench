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
struct shader_var {char* name; int /*<<< orphan*/  mapping; int /*<<< orphan*/  type; } ;
struct shader_struct {int dummy; } ;
struct gl_shader_parser {scalar_t__ type; int /*<<< orphan*/  attribs; int /*<<< orphan*/  gl_string; int /*<<< orphan*/  parser; } ;
struct gl_parser_attrib {int input; int /*<<< orphan*/  mapping; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ GS_SHADER_PIXEL ; 
 scalar_t__ GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct gl_parser_attrib*) ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_parser_attrib_init (struct gl_parser_attrib*) ; 
 int /*<<< orphan*/  gl_unwrap_storage_struct (struct gl_shader_parser*,struct shader_struct*,char*,int,char const*) ; 
 int /*<<< orphan*/  gl_write_type (struct gl_shader_parser*,int /*<<< orphan*/ ) ; 
 struct shader_struct* shader_parser_getstruct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void gl_write_storage_var(struct gl_shader_parser *glsp,
				 struct shader_var *var, bool input,
				 const char *prefix)
{
	struct shader_struct *st =
		shader_parser_getstruct(&glsp->parser, var->type);

	if (st) {
		gl_unwrap_storage_struct(glsp, st, var->name, input, prefix);
	} else {
		if (input && (strcmp(var->mapping, "VERTEXID") == 0))
			return;
		if (strcmp(var->mapping, "POSITION") == 0) {
			if (!input && (glsp->type == GS_SHADER_VERTEX))
				return;
			if (input && (glsp->type == GS_SHADER_PIXEL))
				return;
		}

		struct gl_parser_attrib attrib;
		gl_parser_attrib_init(&attrib);

		dstr_cat(&glsp->gl_string, input ? "in " : "out ");

		if (prefix)
			dstr_cat(&attrib.name, prefix);
		dstr_cat(&attrib.name, var->name);

		gl_write_type(glsp, var->type);
		dstr_cat(&glsp->gl_string, " ");
		dstr_cat_dstr(&glsp->gl_string, &attrib.name);
		dstr_cat(&glsp->gl_string, ";\n");

		attrib.input = input;
		attrib.mapping = var->mapping;
		da_push_back(glsp->attribs, &attrib);
	}
}