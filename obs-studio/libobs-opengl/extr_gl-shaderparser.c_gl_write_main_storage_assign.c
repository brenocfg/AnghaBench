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
struct shader_var {char* name; int /*<<< orphan*/  mapping; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {size_t num; struct shader_var* array; } ;
struct shader_struct {TYPE_1__ vars; } ;
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;
struct gl_shader_parser {scalar_t__ type; struct dstr gl_string; int /*<<< orphan*/  parser; } ;

/* Variables and functions */
 scalar_t__ GS_SHADER_PIXEL ; 
 scalar_t__ GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  gl_write_main_interface_assign (struct gl_shader_parser*,struct shader_var*,char const*) ; 
 struct shader_struct* shader_parser_getstruct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void gl_write_main_storage_assign(struct gl_shader_parser *glsp,
					 struct shader_var *var,
					 const char *dst, const char *src,
					 bool input)
{
	struct shader_struct *st;
	struct dstr dst_copy = {0};
	char ch_left = input ? '.' : '_';
	char ch_right = input ? '_' : '.';

	if (dst) {
		dstr_copy(&dst_copy, dst);
		dstr_cat_ch(&dst_copy, ch_left);
	} else {
		dstr_copy(&dst_copy, "\t");
	}

	dstr_cat(&dst_copy, var->name);

	st = shader_parser_getstruct(&glsp->parser, var->type);
	if (st) {
		struct dstr src_copy = {0};
		size_t i;

		if (src)
			dstr_copy(&src_copy, src);
		dstr_cat(&src_copy, var->name);
		dstr_cat_ch(&src_copy, ch_right);

		for (i = 0; i < st->vars.num; i++) {
			struct shader_var *st_var = st->vars.array + i;
			gl_write_main_storage_assign(glsp, st_var,
						     dst_copy.array,
						     src_copy.array, input);
		}

		dstr_free(&src_copy);
	} else {
		if (input || (glsp->type != GS_SHADER_VERTEX) ||
		    (strcmp(var->mapping, "POSITION"))) {
			if (!dstr_is_empty(&dst_copy))
				dstr_cat_dstr(&glsp->gl_string, &dst_copy);
			dstr_cat(&glsp->gl_string, " = ");
			if (input && (strcmp(var->mapping, "VERTEXID") == 0))
				dstr_cat(&glsp->gl_string, "uint(gl_VertexID)");
			else if (input && (glsp->type == GS_SHADER_PIXEL) &&
				 (strcmp(var->mapping, "POSITION") == 0))
				dstr_cat(&glsp->gl_string, "gl_FragCoord");
			else {
				if (src)
					dstr_cat(&glsp->gl_string, src);
				dstr_cat(&glsp->gl_string, var->name);
			}
			dstr_cat(&glsp->gl_string, ";\n");
		}

		if (!input)
			gl_write_main_interface_assign(glsp, var, src);
	}

	dstr_free(&dst_copy);
}