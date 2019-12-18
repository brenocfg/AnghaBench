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
struct TYPE_3__ {size_t num; struct gl_parser_attrib* array; } ;
struct gl_shader_parser {char* input_prefix; char* output_prefix; int /*<<< orphan*/  gl_string; TYPE_1__ attribs; } ;
struct TYPE_4__ {int /*<<< orphan*/  array; } ;
struct gl_parser_attrib {TYPE_2__ name; scalar_t__ input; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_move (TYPE_2__*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  dstr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_rename_attributes(struct gl_shader_parser *glsp)
{
	size_t i = 0, input_idx = 0, output_idx = 0;

	for (i = 0; i < glsp->attribs.num; i++) {
		struct gl_parser_attrib *attrib = glsp->attribs.array + i;
		struct dstr new_name = {0};
		const char *prefix;
		size_t val;

		if (attrib->input) {
			prefix = glsp->input_prefix;
			val = input_idx++;
		} else {
			prefix = glsp->output_prefix;
			val = output_idx++;
		}

		dstr_printf(&new_name, "%s%u", prefix, (unsigned int)val);
		dstr_replace(&glsp->gl_string, attrib->name.array,
			     new_name.array);
		dstr_move(&attrib->name, &new_name);
	}
}