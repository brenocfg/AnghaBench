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
struct gs_shader {void* world; void* viewproj; } ;
struct TYPE_3__ {size_t num; scalar_t__ array; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct gl_shader_parser {TYPE_2__ parser; } ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  gl_add_param (struct gs_shader*,scalar_t__,int /*<<< orphan*/ *) ; 
 void* gs_shader_get_param_by_name (struct gs_shader*,char*) ; 

__attribute__((used)) static inline bool gl_add_params(struct gs_shader *shader,
				 struct gl_shader_parser *glsp)
{
	size_t i;
	GLint tex_id = 0;

	for (i = 0; i < glsp->parser.params.num; i++)
		if (!gl_add_param(shader, glsp->parser.params.array + i,
				  &tex_id))
			return false;

	shader->viewproj = gs_shader_get_param_by_name(shader, "ViewProj");
	shader->world = gs_shader_get_param_by_name(shader, "World");

	return true;
}