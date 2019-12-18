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
struct wined3d_shader_reg_maps {scalar_t__ fog; scalar_t__ usespow; scalar_t__ usesnrm; } ;
struct wined3d_gl_info {int quirks; int /*<<< orphan*/ * supported; } ;
struct arb_vshader_private {int dummy; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t NV_VERTEX_PROGRAM ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3D_QUIRK_ARB_VS_OFFSET_LIMIT ; 
 int WINED3D_QUIRK_SET_TEXCOORD_W ; 
 scalar_t__ need_rel_addr_const (struct arb_vshader_private const*,struct wined3d_shader_reg_maps const*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  use_nv_clip (struct wined3d_gl_info const*) ; 

__attribute__((used)) static BOOL need_helper_const(const struct arb_vshader_private *shader_data,
        const struct wined3d_shader_reg_maps *reg_maps, const struct wined3d_gl_info *gl_info)
{
    if (need_rel_addr_const(shader_data, reg_maps, gl_info)) return TRUE;
    if (!gl_info->supported[NV_VERTEX_PROGRAM]) return TRUE; /* Need to init colors. */
    if (gl_info->quirks & WINED3D_QUIRK_ARB_VS_OFFSET_LIMIT) return TRUE; /* Load the immval offset. */
    if (gl_info->quirks & WINED3D_QUIRK_SET_TEXCOORD_W) return TRUE; /* Have to init texcoords. */
    if (!use_nv_clip(gl_info)) return TRUE; /* Init the clip texcoord */
    if (reg_maps->usesnrm) return TRUE; /* 0.0 */
    if (reg_maps->usespow) return TRUE; /* EPS, 0.0 and 1.0 */
    if (reg_maps->fog) return TRUE; /* Clamping fog coord, 0.0 and 1.0 */
    return FALSE;
}