#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_6__ {TYPE_4__ attribs; TYPE_4__ params; TYPE_4__ samplers; scalar_t__ obj; } ;
typedef  TYPE_1__ gs_shader_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (TYPE_4__) ; 
 int /*<<< orphan*/  glDeleteShader (scalar_t__) ; 
 int /*<<< orphan*/  gl_success (char*) ; 
 int /*<<< orphan*/  gs_samplerstate_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_program_references (TYPE_1__*) ; 
 int /*<<< orphan*/  shader_attrib_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_param_free (int /*<<< orphan*/ *) ; 

void gs_shader_destroy(gs_shader_t *shader)
{
	size_t i;

	if (!shader)
		return;

	remove_program_references(shader);

	for (i = 0; i < shader->attribs.num; i++)
		shader_attrib_free(shader->attribs.array + i);

	for (i = 0; i < shader->samplers.num; i++)
		gs_samplerstate_destroy(shader->samplers.array[i]);

	for (i = 0; i < shader->params.num; i++)
		shader_param_free(shader->params.array + i);

	if (shader->obj) {
		glDeleteShader(shader->obj);
		gl_success("glDeleteShader");
	}

	da_free(shader->samplers);
	da_free(shader->params);
	da_free(shader->attribs);
	bfree(shader);
}