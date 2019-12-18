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
struct program_param {int obj; struct gs_shader_param* param; } ;
struct gs_shader_param {int /*<<< orphan*/  name; } ;
struct gs_program {int /*<<< orphan*/  params; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct program_param*) ; 
 int glGetUniformLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static bool assign_program_param(struct gs_program *program,
				 struct gs_shader_param *param)
{
	struct program_param info;

	info.obj = glGetUniformLocation(program->obj, param->name);
	if (!gl_success("glGetUniformLocation"))
		return false;

	if (info.obj == -1) {
		return true;
	}

	info.param = param;
	da_push_back(program->params, &info);
	return true;
}