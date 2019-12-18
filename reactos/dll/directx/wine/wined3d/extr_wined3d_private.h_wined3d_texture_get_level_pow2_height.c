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
struct wined3d_texture {unsigned int pow2_height; } ;

/* Variables and functions */
 unsigned int max (int,unsigned int) ; 

__attribute__((used)) static inline unsigned int wined3d_texture_get_level_pow2_height(const struct wined3d_texture *texture,
        unsigned int level)
{
    return max(1, texture->pow2_height >> level);
}