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
struct TYPE_3__ {int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_REGISTER_COMBINERS_NV ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvrc_enable(const struct wined3d_gl_info *gl_info, BOOL enable)
{
    if (enable)
    {
        gl_info->gl_ops.gl.p_glEnable(GL_REGISTER_COMBINERS_NV);
        checkGLcall("glEnable(GL_REGISTER_COMBINERS_NV)");
    }
    else
    {
        gl_info->gl_ops.gl.p_glDisable(GL_REGISTER_COMBINERS_NV);
        checkGLcall("glDisable(GL_REGISTER_COMBINERS_NV)");
    }
}