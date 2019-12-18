#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {TYPE_2__* dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_type; } ;
struct TYPE_4__ {TYPE_1__ reg; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  shader_glsl_append_dst_ext (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD shader_glsl_append_dst(struct wined3d_string_buffer *buffer, const struct wined3d_shader_instruction *ins)
{
    return shader_glsl_append_dst_ext(buffer, ins, &ins->dst[0], ins->dst[0].reg.data_type);
}