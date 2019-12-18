#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* glDeleteRenderbuffers ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_glDeleteTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_3__ fbo_ops; TYPE_2__ gl_ops; } ;
typedef  enum wined3d_gl_resource_type { ____Placeholder_wined3d_gl_resource_type } wined3d_gl_resource_type ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
#define  WINED3D_GL_RES_TYPE_BUFFER 135 
#define  WINED3D_GL_RES_TYPE_COUNT 134 
#define  WINED3D_GL_RES_TYPE_RB 133 
#define  WINED3D_GL_RES_TYPE_TEX_1D 132 
#define  WINED3D_GL_RES_TYPE_TEX_2D 131 
#define  WINED3D_GL_RES_TYPE_TEX_3D 130 
#define  WINED3D_GL_RES_TYPE_TEX_CUBE 129 
#define  WINED3D_GL_RES_TYPE_TEX_RECT 128 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_fbo_attachment(const struct wined3d_gl_info *gl_info,
        enum wined3d_gl_resource_type d3d_type, GLuint object)
{
    switch (d3d_type)
    {
        case WINED3D_GL_RES_TYPE_TEX_1D:
        case WINED3D_GL_RES_TYPE_TEX_2D:
        case WINED3D_GL_RES_TYPE_TEX_RECT:
        case WINED3D_GL_RES_TYPE_TEX_3D:
        case WINED3D_GL_RES_TYPE_TEX_CUBE:
            gl_info->gl_ops.gl.p_glDeleteTextures(1, &object);
            break;

        case WINED3D_GL_RES_TYPE_RB:
            gl_info->fbo_ops.glDeleteRenderbuffers(1, &object);
            break;

        case WINED3D_GL_RES_TYPE_BUFFER:
        case WINED3D_GL_RES_TYPE_COUNT:
            break;
    }
}