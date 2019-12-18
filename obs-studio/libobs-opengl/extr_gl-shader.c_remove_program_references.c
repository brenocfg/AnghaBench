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
struct gs_shader {scalar_t__ type; TYPE_1__* device; } ;
struct gs_program {struct gs_shader* pixel_shader; struct gs_shader* vertex_shader; struct gs_program* next; } ;
struct TYPE_2__ {struct gs_program* first_program; } ;

/* Variables and functions */
 scalar_t__ GS_SHADER_PIXEL ; 
 scalar_t__ GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  gs_program_destroy (struct gs_program*) ; 

__attribute__((used)) static void remove_program_references(struct gs_shader *shader)
{
	struct gs_program *program = shader->device->first_program;

	while (program) {
		struct gs_program *next = program->next;
		bool destroy = false;

		if (shader->type == GS_SHADER_VERTEX &&
		    program->vertex_shader == shader)
			destroy = true;

		else if (shader->type == GS_SHADER_PIXEL &&
			 program->pixel_shader == shader)
			destroy = true;

		if (destroy)
			gs_program_destroy(program);

		program = next;
	}
}