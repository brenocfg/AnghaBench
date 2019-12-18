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
struct wined3d_bo_address {int /*<<< orphan*/  buffer_object; } ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_bind_bo (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUnmapBuffer (int /*<<< orphan*/ ) ; 

void context_unmap_bo_address(struct wined3d_context *context,
        const struct wined3d_bo_address *data, GLenum binding)
{
    const struct wined3d_gl_info *gl_info;

    if (!data->buffer_object)
        return;

    gl_info = context->gl_info;
    context_bind_bo(context, binding, data->buffer_object);
    GL_EXTCALL(glUnmapBuffer(binding));
    context_bind_bo(context, binding, 0);
    checkGLcall("Unmap buffer object");
}