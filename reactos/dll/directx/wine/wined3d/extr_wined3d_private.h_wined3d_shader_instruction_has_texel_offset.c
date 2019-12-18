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
struct TYPE_2__ {scalar_t__ w; scalar_t__ v; scalar_t__ u; } ;
struct wined3d_shader_instruction {TYPE_1__ texel_offset; } ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL wined3d_shader_instruction_has_texel_offset(const struct wined3d_shader_instruction *ins)
{
    return ins->texel_offset.u || ins->texel_offset.v || ins->texel_offset.w;
}