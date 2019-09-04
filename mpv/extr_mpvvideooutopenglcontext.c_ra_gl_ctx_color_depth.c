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
struct ra_swapchain {struct priv* priv; } ;
struct priv {scalar_t__ main_fb; int /*<<< orphan*/  wrapped_fb; TYPE_1__* gl; } ;
struct TYPE_2__ {int es; int mpgl_caps; int /*<<< orphan*/  (* BindFramebuffer ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* GetFramebufferAttachmentParameteriv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;scalar_t__ version; } ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_BACK_LEFT ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE ; 
 int MPGL_CAP_FB ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 

int ra_gl_ctx_color_depth(struct ra_swapchain *sw)
{
    struct priv *p = sw->priv;
    GL *gl = p->gl;

    if (!p->wrapped_fb)
        return 0;

    if ((gl->es < 300 && !gl->version) || !(gl->mpgl_caps & MPGL_CAP_FB))
        return 0;

    gl->BindFramebuffer(GL_FRAMEBUFFER, p->main_fb);

    GLenum obj = gl->version ? GL_BACK_LEFT : GL_BACK;
    if (p->main_fb)
        obj = GL_COLOR_ATTACHMENT0;

    GLint depth_g = 0;

    gl->GetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, obj,
                            GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &depth_g);

    gl->BindFramebuffer(GL_FRAMEBUFFER, 0);

    return depth_g;
}