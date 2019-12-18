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
struct TYPE_2__ {unsigned int depth; } ;
struct wined3d_texture {TYPE_1__ resource; } ;

/* Variables and functions */
 unsigned int max (int,unsigned int) ; 

__attribute__((used)) static inline unsigned int wined3d_texture_get_level_depth(const struct wined3d_texture *texture,
        unsigned int level)
{
    return max(1, texture->resource.depth >> level);
}