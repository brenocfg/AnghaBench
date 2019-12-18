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
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 scalar_t__ GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_INDEXBUFFER ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (scalar_t__,int /*<<< orphan*/ ) ; 

void context_bind_bo(struct wined3d_context *context, GLenum binding, GLuint name)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (binding == GL_ELEMENT_ARRAY_BUFFER)
        context_invalidate_state(context, STATE_INDEXBUFFER);

    GL_EXTCALL(glBindBuffer(binding, name));
}