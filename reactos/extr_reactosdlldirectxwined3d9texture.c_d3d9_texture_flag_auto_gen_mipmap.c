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
struct d3d9_texture {int usage; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3D9_TEXTURE_MIPMAP_DIRTY ; 
 int D3DUSAGE_AUTOGENMIPMAP ; 

void d3d9_texture_flag_auto_gen_mipmap(struct d3d9_texture *texture)
{
    if (texture->usage & D3DUSAGE_AUTOGENMIPMAP)
        texture->flags |= D3D9_TEXTURE_MIPMAP_DIRTY;
}