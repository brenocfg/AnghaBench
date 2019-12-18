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
struct gs_shader_param {int dummy; } ;
struct TYPE_2__ {size_t num; struct gs_shader_param* array; } ;
struct gs_shader {TYPE_1__ params; } ;
struct gs_program {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assign_program_param (struct gs_program*,struct gs_shader_param*) ; 

__attribute__((used)) static inline bool assign_program_shader_params(struct gs_program *program,
						struct gs_shader *shader)
{
	for (size_t i = 0; i < shader->params.num; i++) {
		struct gs_shader_param *param = shader->params.array + i;
		if (!assign_program_param(program, param))
			return false;
	}

	return true;
}