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
struct wined3d_gl_info {scalar_t__* supported; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXT_EMUL_ARB_MULTITEXTURE ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 

__attribute__((used)) static DWORD glsl_fragment_pipe_get_emul_mask(const struct wined3d_gl_info *gl_info)
{
    if (gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
        return GL_EXT_EMUL_ARB_MULTITEXTURE;
    return 0;
}