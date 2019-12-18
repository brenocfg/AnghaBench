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
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_zstencil_buffer {int /*<<< orphan*/  format; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  glGenRenderbuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glRenderbufferStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_renderbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static bool gl_init_zsbuffer(struct gs_zstencil_buffer *zs, uint32_t width,
			     uint32_t height)
{
	glGenRenderbuffers(1, &zs->buffer);
	if (!gl_success("glGenRenderbuffers"))
		return false;

	if (!gl_bind_renderbuffer(GL_RENDERBUFFER, zs->buffer))
		return false;

	glRenderbufferStorage(GL_RENDERBUFFER, zs->format, width, height);
	if (!gl_success("glRenderbufferStorage"))
		return false;

	gl_bind_renderbuffer(GL_RENDERBUFFER, 0);
	return true;
}