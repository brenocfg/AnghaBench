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
struct wined3d_string_buffer {int dummy; } ;
typedef  enum wined3d_shader_input_sysval_semantic { ____Placeholder_wined3d_shader_input_sysval_semantic } wined3d_shader_input_sysval_semantic ;
struct TYPE_3__ {int sysval_semantic; int sysval_name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int) ; 
 TYPE_1__* shader_input_sysval_semantic_names ; 

__attribute__((used)) static void shader_dump_shader_input_sysval_semantic(struct wined3d_string_buffer *buffer,
        enum wined3d_shader_input_sysval_semantic semantic)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(shader_input_sysval_semantic_names); ++i)
    {
        if (shader_input_sysval_semantic_names[i].sysval_semantic == semantic)
        {
            shader_addline(buffer, "%s", shader_input_sysval_semantic_names[i].sysval_name);
            return;
        }
    }

    shader_addline(buffer, "unknown_shader_input_sysval_semantic(%#x)", semantic);
}