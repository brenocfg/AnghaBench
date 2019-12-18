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
struct wined3d_texture {int flags; } ;

/* Variables and functions */
 int WINED3D_TEXTURE_RGB_VALID ; 
 int WINED3D_TEXTURE_SRGB_VALID ; 

__attribute__((used)) static void wined3d_texture_set_dirty(struct wined3d_texture *texture)
{
    texture->flags &= ~(WINED3D_TEXTURE_RGB_VALID | WINED3D_TEXTURE_SRGB_VALID);
}