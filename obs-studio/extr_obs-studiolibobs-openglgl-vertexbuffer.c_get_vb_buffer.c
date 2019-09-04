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
struct TYPE_4__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_3__ {scalar_t__* array; } ;
struct gs_vertex_buffer {TYPE_2__ uv_buffers; TYPE_1__ uv_sizes; int /*<<< orphan*/  color_buffer; int /*<<< orphan*/  tangent_buffer; int /*<<< orphan*/  normal_buffer; int /*<<< orphan*/  vertex_buffer; } ;
typedef  enum attrib_type { ____Placeholder_attrib_type } attrib_type ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int ATTRIB_COLOR ; 
 int ATTRIB_NORMAL ; 
 int ATTRIB_POSITION ; 
 int ATTRIB_TANGENT ; 
 int ATTRIB_TEXCOORD ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 

__attribute__((used)) static inline GLuint get_vb_buffer(struct gs_vertex_buffer *vb,
		enum attrib_type type, size_t index, GLint *width,
		GLenum *gl_type)
{
	*gl_type = GL_FLOAT;
	*width   = 4;

	if (type == ATTRIB_POSITION) {
		return vb->vertex_buffer;
	} else if (type == ATTRIB_NORMAL) {
		return vb->normal_buffer;
	} else if (type == ATTRIB_TANGENT) {
		return vb->tangent_buffer;
	} else if (type == ATTRIB_COLOR) {
		*gl_type = GL_UNSIGNED_BYTE;
		return vb->color_buffer;
	} else if (type == ATTRIB_TEXCOORD) {
		if (vb->uv_buffers.num <= index)
			return 0;

		*width = (GLint)vb->uv_sizes.array[index];
		return vb->uv_buffers.array[index];
	}

	return 0;
}