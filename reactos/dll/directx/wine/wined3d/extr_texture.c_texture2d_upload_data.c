#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  format; } ;
struct wined3d_texture {unsigned int level_count; TYPE_3__ resource; TYPE_2__* sub_resources; } ;
struct wined3d_context {int /*<<< orphan*/  gl_info; } ;
struct wined3d_const_bo_address {int dummy; } ;
struct wined3d_box {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_12__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_11__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_8__ {int /*<<< orphan*/  surface; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_4__ RECT ;
typedef  TYPE_5__ POINT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  wined3d_surface_upload_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,unsigned int,TYPE_5__*,int /*<<< orphan*/ ,struct wined3d_const_bo_address const*) ; 
 scalar_t__ wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 scalar_t__ wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 

__attribute__((used)) static void texture2d_upload_data(struct wined3d_texture *texture, unsigned int sub_resource_idx,
        const struct wined3d_context *context, const struct wined3d_box *box,
        const struct wined3d_const_bo_address *data, unsigned int row_pitch, unsigned int slice_pitch)
{
    unsigned int texture_level;
    POINT dst_point;
    RECT src_rect;

    src_rect.left = 0;
    src_rect.top = 0;
    if (box)
    {
        dst_point.x = box->left;
        dst_point.y = box->top;
        src_rect.right = box->right - box->left;
        src_rect.bottom = box->bottom - box->top;
    }
    else
    {
        dst_point.x = dst_point.y = 0;
        texture_level = sub_resource_idx % texture->level_count;
        src_rect.right = wined3d_texture_get_level_width(texture, texture_level);
        src_rect.bottom = wined3d_texture_get_level_height(texture, texture_level);
    }

    wined3d_surface_upload_data(texture->sub_resources[sub_resource_idx].u.surface, context->gl_info,
            texture->resource.format, &src_rect, row_pitch, &dst_point, FALSE, data);
}