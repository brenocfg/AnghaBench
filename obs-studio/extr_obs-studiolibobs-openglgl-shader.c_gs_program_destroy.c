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
struct gs_program {int /*<<< orphan*/  obj; TYPE_1__* next; TYPE_1__** prev_next; int /*<<< orphan*/  params; int /*<<< orphan*/  attribs; TYPE_2__* device; } ;
struct TYPE_4__ {struct gs_program* cur_program; } ;
struct TYPE_3__ {struct TYPE_3__** prev_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct gs_program*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void gs_program_destroy(struct gs_program *program)
{
	if (!program)
		return;

	if (program->device->cur_program == program) {
		program->device->cur_program = 0;
		glUseProgram(0);
		gl_success("glUseProgram (zero)");
	}

	da_free(program->attribs);
	da_free(program->params);

	if (program->next)
		program->next->prev_next = program->prev_next;
	if (program->prev_next)
		*program->prev_next = program->next;

	glDeleteProgram(program->obj);
	gl_success("glDeleteProgram");

	bfree(program);
}