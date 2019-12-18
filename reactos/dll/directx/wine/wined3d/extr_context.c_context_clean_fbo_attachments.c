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
struct TYPE_4__ {int /*<<< orphan*/  (* glFramebufferTexture2D ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {unsigned int buffers; } ;
struct wined3d_gl_info {TYPE_2__ fbo_ops; TYPE_1__ limits; } ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 scalar_t__ GL_COLOR_ATTACHMENT0 ; 
 scalar_t__ GL_DEPTH_ATTACHMENT ; 
 scalar_t__ GL_STENCIL_ATTACHMENT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_clean_fbo_attachments(const struct wined3d_gl_info *gl_info, GLenum target)
{
    unsigned int i;

    for (i = 0; i < gl_info->limits.buffers; ++i)
    {
        gl_info->fbo_ops.glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
        checkGLcall("glFramebufferTexture2D()");
    }
    gl_info->fbo_ops.glFramebufferTexture2D(target, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    checkGLcall("glFramebufferTexture2D()");

    gl_info->fbo_ops.glFramebufferTexture2D(target, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    checkGLcall("glFramebufferTexture2D()");
}