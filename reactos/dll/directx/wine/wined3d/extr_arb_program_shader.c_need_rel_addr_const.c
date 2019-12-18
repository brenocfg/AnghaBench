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
struct wined3d_shader_reg_maps {int /*<<< orphan*/  usesmova; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct arb_vshader_private {scalar_t__ rel_offset; } ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 size_t NV_VERTEX_PROGRAM2_OPTION ; 
 int TRUE ; 

__attribute__((used)) static BOOL need_rel_addr_const(const struct arb_vshader_private *shader_data,
        const struct wined3d_shader_reg_maps *reg_maps, const struct wined3d_gl_info *gl_info)
{
    if (shader_data->rel_offset) return TRUE;
    if (!reg_maps->usesmova) return FALSE;
    return !gl_info->supported[NV_VERTEX_PROGRAM2_OPTION];
}