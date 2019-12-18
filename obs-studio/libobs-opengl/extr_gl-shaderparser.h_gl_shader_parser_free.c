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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct gl_shader_parser {int /*<<< orphan*/  parser; int /*<<< orphan*/  gl_string; TYPE_1__ texture_samplers; TYPE_1__ attribs; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_parser_attrib_free (scalar_t__) ; 
 int /*<<< orphan*/  shader_parser_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gl_shader_parser_free(struct gl_shader_parser *glsp)
{
	size_t i;
	for (i = 0; i < glsp->attribs.num; i++)
		gl_parser_attrib_free(glsp->attribs.array + i);

	da_free(glsp->attribs);
	da_free(glsp->texture_samplers);
	dstr_free(&glsp->gl_string);
	shader_parser_free(&glsp->parser);
}