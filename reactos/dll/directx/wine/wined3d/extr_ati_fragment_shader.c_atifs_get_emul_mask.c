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
typedef  int DWORD ;

/* Variables and functions */
 int GL_EXT_EMUL_ARB_MULTITEXTURE ; 
 int GL_EXT_EMUL_EXT_FOG_COORD ; 

__attribute__((used)) static DWORD atifs_get_emul_mask(const struct wined3d_gl_info *gl_info)
{
    return GL_EXT_EMUL_ARB_MULTITEXTURE | GL_EXT_EMUL_EXT_FOG_COORD;
}