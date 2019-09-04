#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct gs_program {int /*<<< orphan*/  obj; } ;
struct gs_index_buffer {scalar_t__ width; int /*<<< orphan*/  gl_type; scalar_t__ num; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;
struct TYPE_7__ {TYPE_3__* cur_vertex_buffer; struct gs_index_buffer* cur_index_buffer; struct gs_program* cur_program; } ;
typedef  TYPE_1__ gs_device_t ;
typedef  enum gs_draw_mode { ____Placeholder_gs_draw_mode } gs_draw_mode ;
struct TYPE_8__ {scalar_t__ num; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  can_render (TYPE_1__*) ; 
 int /*<<< orphan*/  convert_gs_topology (int) ; 
 struct gs_program* get_shader_program (TYPE_1__*) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 
 int /*<<< orphan*/  gs_effect_update_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gs_get_effect () ; 
 int /*<<< orphan*/  load_vb_buffers (struct gs_program*,TYPE_3__*,struct gs_index_buffer*) ; 
 int /*<<< orphan*/  program_update_params (struct gs_program*) ; 
 int /*<<< orphan*/  update_viewproj_matrix (TYPE_1__*) ; 

void device_draw(gs_device_t *device, enum gs_draw_mode draw_mode,
		uint32_t start_vert, uint32_t num_verts)
{
	struct gs_index_buffer *ib = device->cur_index_buffer;
	GLenum  topology = convert_gs_topology(draw_mode);
	gs_effect_t *effect = gs_get_effect();
	struct gs_program *program;

	if (!can_render(device))
		goto fail;

	if (effect)
		gs_effect_update_params(effect);

	program = get_shader_program(device);
	if (!program)
		goto fail;

	load_vb_buffers(program, device->cur_vertex_buffer, ib);

	if (program != device->cur_program && device->cur_program) {
		glUseProgram(0);
		gl_success("glUseProgram (zero)");
	}

	if (program != device->cur_program) {
		device->cur_program = program;

		glUseProgram(program->obj);
		if (!gl_success("glUseProgram"))
			goto fail;
	}

	update_viewproj_matrix(device);

	program_update_params(program);

	if (ib) {
		if (num_verts == 0)
			num_verts = (uint32_t)device->cur_index_buffer->num;
		glDrawElements(topology, num_verts, ib->gl_type,
				(const GLvoid*)(start_vert * ib->width));
		if (!gl_success("glDrawElements"))
			goto fail;

	} else {
		if (num_verts == 0)
			num_verts = (uint32_t)device->cur_vertex_buffer->num;
		glDrawArrays(topology, start_vert, num_verts);
		if (!gl_success("glDrawArrays"))
			goto fail;
	}

	return;

fail:
	blog(LOG_ERROR, "device_draw (GL) failed");
}