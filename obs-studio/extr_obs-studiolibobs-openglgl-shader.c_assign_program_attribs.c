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
struct shader_attrib {int dummy; } ;
struct TYPE_2__ {size_t num; struct shader_attrib* array; } ;
struct gs_shader {TYPE_1__ attribs; } ;
struct gs_program {struct gs_shader* vertex_shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  assign_program_attrib (struct gs_program*,struct shader_attrib*) ; 

__attribute__((used)) static inline bool assign_program_attribs(struct gs_program *program)
{
	struct gs_shader *shader = program->vertex_shader;

	for (size_t i = 0; i < shader->attribs.num; i++) {
		struct shader_attrib *attrib = shader->attribs.array + i;
		if (!assign_program_attrib(program, attrib))
			return false;
	}

	return true;
}