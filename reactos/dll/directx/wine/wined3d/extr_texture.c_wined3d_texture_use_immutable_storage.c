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
struct TYPE_2__ {int format_flags; } ;
struct wined3d_texture {TYPE_1__ resource; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_TEXTURE_STORAGE ; 
 int WINED3DFMT_FLAG_HEIGHT_SCALE ; 

__attribute__((used)) static BOOL wined3d_texture_use_immutable_storage(const struct wined3d_texture *texture,
        const struct wined3d_gl_info *gl_info)
{
    /* We don't expect to create texture views for textures with height-scaled formats.
     * Besides, ARB_texture_storage doesn't allow specifying exact sizes for all levels. */
    return gl_info->supported[ARB_TEXTURE_STORAGE]
            && !(texture->resource.format_flags & WINED3DFMT_FLAG_HEIGHT_SCALE);
}