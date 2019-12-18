#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vec3 {int dummy; } ;
struct gs_vb_data {size_t num_tex; int num; struct gs_tvertarray* tvarray; scalar_t__ colors; scalar_t__ tangents; scalar_t__ normals; scalar_t__ points; } ;
struct gs_tvertarray {int width; scalar_t__ array; } ;
struct TYPE_6__ {scalar_t__* array; } ;
struct TYPE_7__ {TYPE_2__ uv_buffers; scalar_t__ color_buffer; scalar_t__ tangent_buffer; scalar_t__ normal_buffer; scalar_t__ vertex_buffer; int /*<<< orphan*/  dynamic; TYPE_1__* data; } ;
typedef  TYPE_3__ gs_vertbuffer_t ;
struct TYPE_5__ {size_t num_tex; } ;
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_buffer (int /*<<< orphan*/ ,scalar_t__,scalar_t__,size_t) ; 

__attribute__((used)) static inline void gs_vertexbuffer_flush_internal(gs_vertbuffer_t *vb,
						  const struct gs_vb_data *data)
{
	size_t i;
	size_t num_tex = data->num_tex < vb->data->num_tex ? data->num_tex
							   : vb->data->num_tex;

	if (!vb->dynamic) {
		blog(LOG_ERROR, "vertex buffer is not dynamic");
		goto failed;
	}

	if (data->points) {
		if (!update_buffer(GL_ARRAY_BUFFER, vb->vertex_buffer,
				   data->points,
				   data->num * sizeof(struct vec3)))
			goto failed;
	}

	if (vb->normal_buffer && data->normals) {
		if (!update_buffer(GL_ARRAY_BUFFER, vb->normal_buffer,
				   data->normals,
				   data->num * sizeof(struct vec3)))
			goto failed;
	}

	if (vb->tangent_buffer && data->tangents) {
		if (!update_buffer(GL_ARRAY_BUFFER, vb->tangent_buffer,
				   data->tangents,
				   data->num * sizeof(struct vec3)))
			goto failed;
	}

	if (vb->color_buffer && data->colors) {
		if (!update_buffer(GL_ARRAY_BUFFER, vb->color_buffer,
				   data->colors, data->num * sizeof(uint32_t)))
			goto failed;
	}

	for (i = 0; i < num_tex; i++) {
		GLuint buffer = vb->uv_buffers.array[i];
		struct gs_tvertarray *tv = data->tvarray + i;
		size_t size = data->num * tv->width * sizeof(float);

		if (!update_buffer(GL_ARRAY_BUFFER, buffer, tv->array, size))
			goto failed;
	}

	return;

failed:
	blog(LOG_ERROR, "gs_vertexbuffer_flush (GL) failed");
}