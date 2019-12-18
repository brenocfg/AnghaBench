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
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_format {int /*<<< orphan*/  component_count; int /*<<< orphan*/  gl_vtx_type; int /*<<< orphan*/  attribute_size; int /*<<< orphan*/  gl_normalized; int /*<<< orphan*/  gl_vtx_format; int /*<<< orphan*/  emit_idx; } ;
struct TYPE_3__ {size_t extension; int /*<<< orphan*/  id; int /*<<< orphan*/  gl_normalized; int /*<<< orphan*/  component_count; int /*<<< orphan*/  gl_vtx_type; int /*<<< orphan*/  emit_idx; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  calculate_vertex_attribute_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dformat (int /*<<< orphan*/ ) ; 
 TYPE_1__* format_vertex_info ; 
 struct wined3d_format* get_format_internal (struct wined3d_gl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL init_format_vertex_info(struct wined3d_gl_info *gl_info)
{
    struct wined3d_format *format;
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(format_vertex_info); ++i)
    {
        if (!(format = get_format_internal(gl_info, format_vertex_info[i].id)))
            return FALSE;

        if (!gl_info->supported[format_vertex_info[i].extension])
            continue;

        format->emit_idx = format_vertex_info[i].emit_idx;
        format->component_count = format_vertex_info[i].component_count;
        format->gl_vtx_type = format_vertex_info[i].gl_vtx_type;
        format->gl_vtx_format = format_vertex_info[i].component_count;
        format->gl_normalized = format_vertex_info[i].gl_normalized;
        if (!(format->attribute_size = calculate_vertex_attribute_size(format->gl_vtx_type,
                format->component_count)))
        {
            ERR("Invalid attribute size for vertex format %s (%#x).\n",
                    debug_d3dformat(format_vertex_info[i].id), format_vertex_info[i].id);
            return FALSE;
        }
    }

    return TRUE;
}