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
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_format {int /*<<< orphan*/  color_fixup; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_TEXTURE_SWIZZLE ; 
 int /*<<< orphan*/  is_complex_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_scaling_fixup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL can_use_texture_swizzle(const struct wined3d_gl_info *gl_info, const struct wined3d_format *format)
{
    return gl_info->supported[ARB_TEXTURE_SWIZZLE] && !is_complex_fixup(format->color_fixup)
            && !is_scaling_fixup(format->color_fixup);
}