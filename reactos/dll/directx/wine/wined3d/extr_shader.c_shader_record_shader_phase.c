#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_phase {int /*<<< orphan*/  const* start; int /*<<< orphan*/  const* end; } ;
struct wined3d_shader_instruction {int handler_idx; } ;
struct TYPE_8__ {int /*<<< orphan*/  join_count; struct wined3d_shader_phase* join; int /*<<< orphan*/  join_size; int /*<<< orphan*/  fork_count; struct wined3d_shader_phase* fork; int /*<<< orphan*/  fork_size; struct wined3d_shader_phase* control_point; } ;
struct TYPE_9__ {TYPE_3__ phases; } ;
struct TYPE_10__ {TYPE_4__ hs; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_1__ shader_version; } ;
struct wined3d_shader {TYPE_5__ u; TYPE_2__ reg_maps; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*) ; 
#define  WINED3DSIH_HS_CONTROL_POINT_PHASE 130 
#define  WINED3DSIH_HS_FORK_PHASE 129 
#define  WINED3DSIH_HS_JOIN_PHASE 128 
 int /*<<< orphan*/  WINED3D_OK ; 
 scalar_t__ WINED3D_SHADER_TYPE_HULL ; 
 scalar_t__ debug_d3dshaderinstructionhandler (int) ; 
 struct wined3d_shader_phase* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (struct wined3d_shader_phase*) ; 
 int /*<<< orphan*/  wined3d_array_reserve (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT shader_record_shader_phase(struct wined3d_shader *shader,
        struct wined3d_shader_phase **current_phase, const struct wined3d_shader_instruction *ins,
        const DWORD *current_instruction_ptr, const DWORD *previous_instruction_ptr)
{
    struct wined3d_shader_phase *phase;

    if ((phase = *current_phase))
    {
        phase->end = previous_instruction_ptr;
        *current_phase = NULL;
    }

    if (shader->reg_maps.shader_version.type != WINED3D_SHADER_TYPE_HULL)
    {
        ERR("Unexpected shader type %#x.\n", shader->reg_maps.shader_version.type);
        return E_FAIL;
    }

    switch (ins->handler_idx)
    {
        case WINED3DSIH_HS_CONTROL_POINT_PHASE:
            if (shader->u.hs.phases.control_point)
            {
                FIXME("Multiple control point phases.\n");
                heap_free(shader->u.hs.phases.control_point);
            }
            if (!(shader->u.hs.phases.control_point = heap_alloc_zero(sizeof(*shader->u.hs.phases.control_point))))
                return E_OUTOFMEMORY;
            phase = shader->u.hs.phases.control_point;
            break;
        case WINED3DSIH_HS_FORK_PHASE:
            if (!wined3d_array_reserve((void **)&shader->u.hs.phases.fork,
                    &shader->u.hs.phases.fork_size, shader->u.hs.phases.fork_count + 1,
                    sizeof(*shader->u.hs.phases.fork)))
                return E_OUTOFMEMORY;
            phase = &shader->u.hs.phases.fork[shader->u.hs.phases.fork_count++];
            break;
        case WINED3DSIH_HS_JOIN_PHASE:
            if (!wined3d_array_reserve((void **)&shader->u.hs.phases.join,
                    &shader->u.hs.phases.join_size, shader->u.hs.phases.join_count + 1,
                    sizeof(*shader->u.hs.phases.join)))
                return E_OUTOFMEMORY;
            phase = &shader->u.hs.phases.join[shader->u.hs.phases.join_count++];
            break;
        default:
            ERR("Unexpected opcode %s.\n", debug_d3dshaderinstructionhandler(ins->handler_idx));
            return E_FAIL;
    }

    phase->start = current_instruction_ptr;
    *current_phase = phase;

    return WINED3D_OK;
}