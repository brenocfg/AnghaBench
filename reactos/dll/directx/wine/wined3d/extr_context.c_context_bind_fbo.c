#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* glBindFramebuffer ) (int /*<<< orphan*/ ,void*) ;} ;
struct wined3d_gl_info {TYPE_1__ fbo_ops; } ;
struct wined3d_context {void* fbo_read_binding; void* fbo_draw_binding; struct wined3d_gl_info* gl_info; } ;
typedef  void* GLuint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  GL_DRAW_FRAMEBUFFER 130 
#define  GL_FRAMEBUFFER 129 
#define  GL_READ_FRAMEBUFFER 128 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void context_bind_fbo(struct wined3d_context *context, GLenum target, GLuint fbo)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    switch (target)
    {
        case GL_READ_FRAMEBUFFER:
            if (context->fbo_read_binding == fbo) return;
            context->fbo_read_binding = fbo;
            break;

        case GL_DRAW_FRAMEBUFFER:
            if (context->fbo_draw_binding == fbo) return;
            context->fbo_draw_binding = fbo;
            break;

        case GL_FRAMEBUFFER:
            if (context->fbo_read_binding == fbo
                    && context->fbo_draw_binding == fbo) return;
            context->fbo_read_binding = fbo;
            context->fbo_draw_binding = fbo;
            break;

        default:
            FIXME("Unhandled target %#x.\n", target);
            break;
    }

    gl_info->fbo_ops.glBindFramebuffer(target, fbo);
    checkGLcall("glBindFramebuffer()");
}