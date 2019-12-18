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
struct wined3d_context {size_t* rev_tex_unit_map; size_t* tex_unit_map; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,size_t,size_t) ; 
 size_t WINED3D_UNMAPPED_STAGE ; 

__attribute__((used)) static void context_map_stage(struct wined3d_context *context, DWORD stage, DWORD unit)
{
    DWORD i = context->rev_tex_unit_map[unit];
    DWORD j = context->tex_unit_map[stage];

    TRACE("Mapping stage %u to unit %u.\n", stage, unit);
    context->tex_unit_map[stage] = unit;
    if (i != WINED3D_UNMAPPED_STAGE && i != stage)
        context->tex_unit_map[i] = WINED3D_UNMAPPED_STAGE;

    context->rev_tex_unit_map[unit] = stage;
    if (j != WINED3D_UNMAPPED_STAGE && j != unit)
        context->rev_tex_unit_map[j] = WINED3D_UNMAPPED_STAGE;
}