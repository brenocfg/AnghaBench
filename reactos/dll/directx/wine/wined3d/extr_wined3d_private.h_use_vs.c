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
struct wined3d_state {TYPE_1__* vertex_declaration; scalar_t__* shader; } ;
struct TYPE_2__ {int /*<<< orphan*/  position_transformed; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t WINED3D_SHADER_TYPE_VERTEX ; 

__attribute__((used)) static inline BOOL use_vs(const struct wined3d_state *state)
{
    /* Check state->vertex_declaration to allow this to be used before the
     * stream info is validated, for example in device_update_tex_unit_map(). */
    return state->shader[WINED3D_SHADER_TYPE_VERTEX]
            && (!state->vertex_declaration || !state->vertex_declaration->position_transformed);
}