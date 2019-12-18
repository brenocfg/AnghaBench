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
struct wined3d_shader_src_param {int /*<<< orphan*/  swizzle; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_glsl_swizzle_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ shader_is_scalar (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_glsl_get_swizzle(const struct wined3d_shader_src_param *param,
        BOOL fixup, DWORD mask, char *swizzle_str)
{
    if (shader_is_scalar(&param->reg))
        *swizzle_str = '\0';
    else
        shader_glsl_swizzle_to_str(param->swizzle, fixup, mask, swizzle_str);
}