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
struct wined3d_vertex_element {int format; size_t offset; int usage; size_t usage_idx; int /*<<< orphan*/  method; scalar_t__ instance_data_step_rate; int /*<<< orphan*/  input_slot_class; int /*<<< orphan*/  output_slot; scalar_t__ input_slot; } ;
struct wined3d_fvf_convert_state {size_t offset; size_t idx; int /*<<< orphan*/  gl_info; struct wined3d_vertex_element* elements; } ;
struct wined3d_format {scalar_t__ attribute_size; } ;
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
typedef  enum wined3d_decl_usage { ____Placeholder_wined3d_decl_usage } wined3d_decl_usage ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_DECL_METHOD_DEFAULT ; 
 int /*<<< orphan*/  WINED3D_INPUT_PER_VERTEX_DATA ; 
 int /*<<< orphan*/  WINED3D_OUTPUT_SLOT_SEMANTIC ; 
 struct wined3d_format* wined3d_get_format (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void append_decl_element(struct wined3d_fvf_convert_state *state,
        enum wined3d_format_id format_id, enum wined3d_decl_usage usage, UINT usage_idx)
{
    struct wined3d_vertex_element *elements = state->elements;
    const struct wined3d_format *format;
    UINT offset = state->offset;
    UINT idx = state->idx;

    elements[idx].format = format_id;
    elements[idx].input_slot = 0;
    elements[idx].offset = offset;
    elements[idx].output_slot = WINED3D_OUTPUT_SLOT_SEMANTIC;
    elements[idx].input_slot_class = WINED3D_INPUT_PER_VERTEX_DATA;
    elements[idx].instance_data_step_rate = 0;
    elements[idx].method = WINED3D_DECL_METHOD_DEFAULT;
    elements[idx].usage = usage;
    elements[idx].usage_idx = usage_idx;

    format = wined3d_get_format(state->gl_info, format_id, 0);
    state->offset += format->attribute_size;
    ++state->idx;
}