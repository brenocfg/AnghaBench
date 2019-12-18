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
struct wined3d_shader_semantic {int usage; int usage_idx; int /*<<< orphan*/  reg; int /*<<< orphan*/  resource_data_type; int /*<<< orphan*/  resource_type; } ;
typedef  enum wined3d_sm1_resource_type { ____Placeholder_wined3d_sm1_resource_type } wined3d_sm1_resource_type ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINED3D_DATA_FLOAT ; 
 int /*<<< orphan*/  WINED3D_SHADER_RESOURCE_NONE ; 
 int WINED3D_SM1_DCL_USAGE_INDEX_MASK ; 
 int WINED3D_SM1_DCL_USAGE_INDEX_SHIFT ; 
 int WINED3D_SM1_DCL_USAGE_MASK ; 
 int WINED3D_SM1_DCL_USAGE_SHIFT ; 
 int WINED3D_SM1_RESOURCE_TYPE_MASK ; 
 int WINED3D_SM1_RESOURCE_TYPE_SHIFT ; 
 int /*<<< orphan*/ * resource_type_table ; 
 int /*<<< orphan*/  shader_parse_dst_param (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_sm1_read_semantic(const DWORD **ptr, struct wined3d_shader_semantic *semantic)
{
    enum wined3d_sm1_resource_type resource_type;
    DWORD usage_token = *(*ptr)++;
    DWORD dst_token = *(*ptr)++;

    semantic->usage = (usage_token & WINED3D_SM1_DCL_USAGE_MASK) >> WINED3D_SM1_DCL_USAGE_SHIFT;
    semantic->usage_idx = (usage_token & WINED3D_SM1_DCL_USAGE_INDEX_MASK) >> WINED3D_SM1_DCL_USAGE_INDEX_SHIFT;
    resource_type = (usage_token & WINED3D_SM1_RESOURCE_TYPE_MASK) >> WINED3D_SM1_RESOURCE_TYPE_SHIFT;
    if (resource_type >= ARRAY_SIZE(resource_type_table))
    {
        FIXME("Unhandled resource type %#x.\n", resource_type);
        semantic->resource_type = WINED3D_SHADER_RESOURCE_NONE;
    }
    else
    {
        semantic->resource_type = resource_type_table[resource_type];
    }
    semantic->resource_data_type = WINED3D_DATA_FLOAT;
    shader_parse_dst_param(dst_token, NULL, &semantic->reg);
}