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
struct d3d9_texture {int flags; int /*<<< orphan*/  wined3d_srv; } ;

/* Variables and functions */
 int D3D9_TEXTURE_MIPMAP_DIRTY ; 
 int /*<<< orphan*/  d3d9_texture_acquire_shader_resource_view (struct d3d9_texture*) ; 
 int /*<<< orphan*/  wined3d_shader_resource_view_generate_mipmaps (int /*<<< orphan*/ ) ; 

void d3d9_texture_gen_auto_mipmap(struct d3d9_texture *texture)
{
    if (!(texture->flags & D3D9_TEXTURE_MIPMAP_DIRTY))
        return;
    d3d9_texture_acquire_shader_resource_view(texture);
    wined3d_shader_resource_view_generate_mipmaps(texture->wined3d_srv);
    texture->flags &= ~D3D9_TEXTURE_MIPMAP_DIRTY;
}