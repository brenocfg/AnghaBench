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
struct wined3d_gl_info {int /*<<< orphan*/ * formats; } ;
struct wined3d_caps_gl_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vendor; } ;
struct wined3d_adapter {int /*<<< orphan*/  d3d_info; TYPE_1__ driver_info; struct wined3d_gl_info gl_info; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apply_format_fixups (struct wined3d_adapter*,struct wined3d_gl_info*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_format_base_info (struct wined3d_gl_info*) ; 
 int /*<<< orphan*/  init_format_block_info (struct wined3d_gl_info*) ; 
 int /*<<< orphan*/  init_format_depth_bias_scale (struct wined3d_caps_gl_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_format_fbo_compat_info (struct wined3d_caps_gl_ctx*) ; 
 int /*<<< orphan*/  init_format_filter_info (struct wined3d_gl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_format_gen_mipmap_info (struct wined3d_gl_info*) ; 
 int /*<<< orphan*/  init_format_texture_info (struct wined3d_adapter*,struct wined3d_gl_info*) ; 
 int /*<<< orphan*/  init_format_vertex_info (struct wined3d_gl_info*) ; 
 int /*<<< orphan*/  init_typeless_formats (struct wined3d_gl_info*) ; 

BOOL wined3d_adapter_init_format_info(struct wined3d_adapter *adapter, struct wined3d_caps_gl_ctx *ctx)
{
    struct wined3d_gl_info *gl_info = &adapter->gl_info;

    if (!init_format_base_info(gl_info)) return FALSE;
    if (!init_format_block_info(gl_info)) goto fail;

    if (!ctx) /* WINED3D_NO3D */
        return TRUE;

    if (!init_format_texture_info(adapter, gl_info)) goto fail;
    if (!init_format_vertex_info(gl_info)) goto fail;

    apply_format_fixups(adapter, gl_info);
    init_format_fbo_compat_info(ctx);
    init_format_filter_info(gl_info, adapter->driver_info.vendor);
    if (!init_typeless_formats(gl_info)) goto fail;
    init_format_gen_mipmap_info(gl_info);
    init_format_depth_bias_scale(ctx, &adapter->d3d_info);

    return TRUE;

fail:
    heap_free(gl_info->formats);
    gl_info->formats = NULL;
    return FALSE;
}