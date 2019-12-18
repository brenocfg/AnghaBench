#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_signature_element {int /*<<< orphan*/  mask; int /*<<< orphan*/  register_idx; int /*<<< orphan*/  component_type; int /*<<< orphan*/  sysval_semantic; scalar_t__ stream_idx; int /*<<< orphan*/  semantic_idx; int /*<<< orphan*/  semantic_name; } ;
struct TYPE_5__ {TYPE_1__* idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  write_mask; TYPE_2__ reg; } ;
struct wined3d_shader_semantic {TYPE_3__ reg; int /*<<< orphan*/  usage; int /*<<< orphan*/  usage_idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_TYPE_FLOAT ; 
 int /*<<< orphan*/  shader_semantic_name_from_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_sysval_semantic_from_usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_signature_from_semantic(struct wined3d_shader_signature_element *e,
        const struct wined3d_shader_semantic *s)
{
    e->semantic_name = shader_semantic_name_from_usage(s->usage);
    e->semantic_idx = s->usage_idx;
    e->stream_idx = 0;
    e->sysval_semantic = shader_sysval_semantic_from_usage(s->usage);
    e->component_type = WINED3D_TYPE_FLOAT;
    e->register_idx = s->reg.reg.idx[0].offset;
    e->mask = s->reg.write_mask;
}