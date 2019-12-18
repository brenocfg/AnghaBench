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
struct TYPE_2__ {int major; } ;
struct wined3d_shader_reg_maps {int texcoord; int input_registers; TYPE_1__ shader_version; } ;
typedef  int DWORD ;

/* Variables and functions */
 unsigned int wined3d_log2i (int) ; 

unsigned int shader_find_free_input_register(const struct wined3d_shader_reg_maps *reg_maps, unsigned int max)
{
    DWORD map = 1u << max;
    map |= map - 1;
    map &= reg_maps->shader_version.major < 3 ? ~reg_maps->texcoord : ~reg_maps->input_registers;

    return wined3d_log2i(map);
}