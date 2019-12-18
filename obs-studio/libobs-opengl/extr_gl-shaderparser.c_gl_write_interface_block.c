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
struct gl_shader_parser {scalar_t__ type; int /*<<< orphan*/  gl_string; } ;

/* Variables and functions */
 scalar_t__ GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void gl_write_interface_block(struct gl_shader_parser *glsp)
{
	if (glsp->type == GS_SHADER_VERTEX) {
		dstr_cat(&glsp->gl_string, "out gl_PerVertex {\n"
					   "\tvec4 gl_Position;\n};\n\n");
	}
}