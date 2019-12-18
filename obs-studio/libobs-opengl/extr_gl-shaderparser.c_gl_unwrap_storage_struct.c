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
struct shader_var {int dummy; } ;
struct TYPE_2__ {size_t num; struct shader_var* array; } ;
struct shader_struct {TYPE_1__ vars; } ;
struct gl_shader_parser {int dummy; } ;
struct dstr {int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  gl_write_storage_var (struct gl_shader_parser*,struct shader_var*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_unwrap_storage_struct(struct gl_shader_parser *glsp,
				     struct shader_struct *st, const char *name,
				     bool input, const char *prefix)
{
	struct dstr prefix_str;
	size_t i;

	dstr_init(&prefix_str);
	if (prefix)
		dstr_copy(&prefix_str, prefix);
	dstr_cat(&prefix_str, name);
	dstr_cat(&prefix_str, "_");

	for (i = 0; i < st->vars.num; i++) {
		struct shader_var *st_var = st->vars.array + i;
		gl_write_storage_var(glsp, st_var, input, prefix_str.array);
	}

	dstr_free(&prefix_str);
}