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
typedef  enum wined3d_cmp_func { ____Placeholder_wined3d_cmp_func } wined3d_cmp_func ;

/* Variables and functions */
 int WINED3D_CMP_ALWAYS ; 
 int WINED3D_CMP_NEVER ; 

__attribute__((used)) static inline enum wined3d_cmp_func wined3d_sanitize_cmp_func(enum wined3d_cmp_func func)
{
    if (func < WINED3D_CMP_NEVER || func > WINED3D_CMP_ALWAYS)
        return WINED3D_CMP_ALWAYS;
    return func;
}