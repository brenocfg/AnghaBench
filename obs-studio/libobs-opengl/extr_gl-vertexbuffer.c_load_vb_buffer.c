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
struct shader_attrib {int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;
struct gs_vertex_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_vb_buffer (struct gs_vertex_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static bool load_vb_buffer(struct shader_attrib *attrib,
			   struct gs_vertex_buffer *vb, GLint id)
{
	GLenum type;
	GLint width;
	GLuint buffer;
	bool success = true;

	buffer = get_vb_buffer(vb, attrib->type, attrib->index, &width, &type);
	if (!buffer) {
		blog(LOG_ERROR, "Vertex buffer does not have the required "
				"inputs for vertex shader");
		return false;
	}

	if (!gl_bind_buffer(GL_ARRAY_BUFFER, buffer))
		return false;

	glVertexAttribPointer(id, width, type, GL_TRUE, 0, 0);
	if (!gl_success("glVertexAttribPointer"))
		success = false;

	glEnableVertexAttribArray(id);
	if (!gl_success("glEnableVertexAttribArray"))
		success = false;

	if (!gl_bind_buffer(GL_ARRAY_BUFFER, 0))
		success = false;

	return success;
}