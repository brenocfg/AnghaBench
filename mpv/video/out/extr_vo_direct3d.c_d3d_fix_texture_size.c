#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  opt_disable_texture_align; scalar_t__ device_caps_square_only; scalar_t__ device_caps_power2_only; } ;
typedef  TYPE_1__ d3d_priv ;

/* Variables and functions */
 int MPMAX (int,int) ; 

__attribute__((used)) static void d3d_fix_texture_size(d3d_priv *priv, int *width, int *height)
{
    int tex_width = *width;
    int tex_height = *height;

    // avoid nasty special cases with 0-sized textures and texture sizes
    tex_width = MPMAX(tex_width, 1);
    tex_height = MPMAX(tex_height, 1);

    if (priv->device_caps_power2_only) {
        tex_width  = 1;
        tex_height = 1;
        while (tex_width  < *width) tex_width  <<= 1;
        while (tex_height < *height) tex_height <<= 1;
    }
    if (priv->device_caps_square_only)
        /* device only supports square textures */
        tex_width = tex_height = MPMAX(tex_width, tex_height);
    // better round up to a multiple of 16
    if (!priv->opt_disable_texture_align) {
        tex_width  = (tex_width  + 15) & ~15;
        tex_height = (tex_height + 15) & ~15;
    }

    *width = tex_width;
    *height = tex_height;
}