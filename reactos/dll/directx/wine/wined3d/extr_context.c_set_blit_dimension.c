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
struct TYPE_4__ {int /*<<< orphan*/  (* p_glViewport ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double) ;int /*<<< orphan*/  (* p_glLoadMatrixd ) (double const*) ;int /*<<< orphan*/  (* p_glMatrixMode ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_1__ gl_ops; scalar_t__* supported; } ;
typedef  double UINT ;
typedef  double GLdouble ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PROJECTION ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (double const*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double) ; 

__attribute__((used)) static void set_blit_dimension(const struct wined3d_gl_info *gl_info, UINT width, UINT height)
{
    const GLdouble projection[] =
    {
        2.0 / width,          0.0,  0.0, 0.0,
                0.0, 2.0 / height,  0.0, 0.0,
                0.0,          0.0,  2.0, 0.0,
               -1.0,         -1.0, -1.0, 1.0,
    };

    if (gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
    {
        gl_info->gl_ops.gl.p_glMatrixMode(GL_PROJECTION);
        checkGLcall("glMatrixMode(GL_PROJECTION)");
        gl_info->gl_ops.gl.p_glLoadMatrixd(projection);
        checkGLcall("glLoadMatrixd");
    }
    gl_info->gl_ops.gl.p_glViewport(0, 0, width, height);
    checkGLcall("glViewport");
}