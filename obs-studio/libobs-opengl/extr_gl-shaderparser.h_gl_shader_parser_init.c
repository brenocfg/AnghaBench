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
struct gl_shader_parser {int type; char* input_prefix; char* output_prefix; int /*<<< orphan*/  attribs; int /*<<< orphan*/  texture_samplers; int /*<<< orphan*/  gl_string; int /*<<< orphan*/  parser; } ;
typedef  enum gs_shader_type { ____Placeholder_gs_shader_type } gs_shader_type ;

/* Variables and functions */
 int GS_SHADER_PIXEL ; 
 int GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_parser_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gl_shader_parser_init(struct gl_shader_parser *glsp,
					 enum gs_shader_type type)
{
	glsp->type = type;

	if (type == GS_SHADER_VERTEX) {
		glsp->input_prefix = "_input_attrib";
		glsp->output_prefix = "_vertex_shader_attrib";
	} else if (type == GS_SHADER_PIXEL) {
		glsp->input_prefix = "_vertex_shader_attrib";
		glsp->output_prefix = "_pixel_shader_attrib";
	}

	shader_parser_init(&glsp->parser);
	dstr_init(&glsp->gl_string);
	da_init(glsp->texture_samplers);
	da_init(glsp->attribs);
}