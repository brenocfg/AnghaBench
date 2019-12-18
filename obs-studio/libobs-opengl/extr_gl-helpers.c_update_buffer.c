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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int GL_MAP_INVALIDATE_BUFFER_BIT ; 
 int GL_MAP_WRITE_BIT ; 
 void* glMapBufferRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  glUnmapBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gl_success (char*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

bool update_buffer(GLenum target, GLuint buffer, const void *data, size_t size)
{
	void *ptr;
	bool success = true;

	if (!gl_bind_buffer(target, buffer))
		return false;

	/* glMapBufferRange with these flags will actually give far better
	 * performance than a plain glMapBuffer call */
	ptr = glMapBufferRange(target, 0, size,
			       GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	success = gl_success("glMapBufferRange");
	if (success && ptr) {
		memcpy(ptr, data, size);
		glUnmapBuffer(target);
	}

	gl_bind_buffer(target, 0);
	return success;
}