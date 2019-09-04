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
struct program_param {int dummy; } ;
struct TYPE_2__ {size_t num; struct program_param* array; } ;
struct gs_program {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  program_set_param_data (struct gs_program*,struct program_param*) ; 

void program_update_params(struct gs_program *program)
{
	for (size_t i = 0; i < program->params.num; i++) {
		struct program_param *pp = program->params.array + i;
		program_set_param_data(program, pp);
	}
}