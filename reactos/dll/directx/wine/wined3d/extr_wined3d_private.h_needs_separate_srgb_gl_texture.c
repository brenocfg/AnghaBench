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
struct TYPE_4__ {unsigned int format_flags; } ;
struct wined3d_texture {TYPE_1__ resource; } ;
struct wined3d_context {TYPE_3__* d3d_info; TYPE_2__* gl_info; } ;
struct TYPE_6__ {int wined3d_creation_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * supported; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t EXT_TEXTURE_SRGB_DECODE ; 
 unsigned int WINED3DFMT_FLAG_SRGB_READ ; 
 unsigned int WINED3DFMT_FLAG_SRGB_WRITE ; 
 int WINED3D_SRGB_READ_WRITE_CONTROL ; 

__attribute__((used)) static inline BOOL needs_separate_srgb_gl_texture(const struct wined3d_context *context,
        const struct wined3d_texture *texture)
{
    unsigned int flags = texture->resource.format_flags
            & (WINED3DFMT_FLAG_SRGB_READ | WINED3DFMT_FLAG_SRGB_WRITE);

    return (!context->gl_info->supported[EXT_TEXTURE_SRGB_DECODE]
            || (flags && flags != (WINED3DFMT_FLAG_SRGB_READ | WINED3DFMT_FLAG_SRGB_WRITE)))
            && context->d3d_info->wined3d_creation_flags & WINED3D_SRGB_READ_WRITE_CONTROL;
}