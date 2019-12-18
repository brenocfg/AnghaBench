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
struct wined3d_vertex_pipe_ops {struct StateEntryTemplate* vp_states; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_d3d_info {int dummy; } ;
struct fragment_pipeline {struct StateEntryTemplate* states; } ;
struct TYPE_2__ {scalar_t__ representative; int /*<<< orphan*/  apply; } ;
struct StateEntryTemplate {int state; size_t extension; TYPE_1__ content; } ;
struct StateEntry {scalar_t__ representative; int /*<<< orphan*/  apply; } ;
typedef  int /*<<< orphan*/  set ;
typedef  int /*<<< orphan*/  multistate_funcs ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BOOL ;
typedef  int /*<<< orphan*/  APPLYSTATEFUNC ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t,unsigned int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,size_t) ; 
 int STATE_HIGHEST ; 
 int /*<<< orphan*/ * TRUE ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 int /*<<< orphan*/  debug_d3dstate (size_t) ; 
 int /*<<< orphan*/ * heap_calloc (int,int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multistate_apply_2 ; 
 int /*<<< orphan*/  multistate_apply_3 ; 
 unsigned int num_handlers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prune_invalid_states (struct StateEntry*,struct wined3d_gl_info const*,struct wined3d_d3d_info const*) ; 
 int /*<<< orphan*/  state_undefined ; 
 int /*<<< orphan*/  validate_state_table (struct StateEntry*) ; 

HRESULT compile_state_table(struct StateEntry *StateTable, APPLYSTATEFUNC **dev_multistate_funcs,
        const struct wined3d_gl_info *gl_info, const struct wined3d_d3d_info *d3d_info,
        const struct wined3d_vertex_pipe_ops *vertex, const struct fragment_pipeline *fragment,
        const struct StateEntryTemplate *misc)
{
    unsigned int i, type, handlers;
    APPLYSTATEFUNC multistate_funcs[STATE_HIGHEST + 1][3];
    const struct StateEntryTemplate *cur;
    BOOL set[STATE_HIGHEST + 1];

    memset(multistate_funcs, 0, sizeof(multistate_funcs));

    for(i = 0; i < STATE_HIGHEST + 1; i++) {
        StateTable[i].representative = 0;
        StateTable[i].apply = state_undefined;
    }

    for(type = 0; type < 3; type++) {
        /* This switch decides the order in which the states are applied */
        switch(type) {
            case 0: cur = misc; break;
            case 1: cur = fragment->states; break;
            case 2: cur = vertex->vp_states; break;
            default: cur = NULL; /* Stupid compiler */
        }
        if(!cur) continue;

        /* GL extension filtering should not prevent multiple handlers being applied from different
         * pipeline parts
         */
        memset(set, 0, sizeof(set));

        for(i = 0; cur[i].state; i++) {
            APPLYSTATEFUNC *funcs_array;

            /* Only use the first matching state with the available extension from one template.
             * e.g.
             * {D3DRS_FOOBAR, {D3DRS_FOOBAR, func1}, XYZ_FANCY},
             * {D3DRS_FOOBAR, {D3DRS_FOOBAR, func2}, 0        }
             *
             * if GL_XYZ_fancy is supported, ignore the 2nd line
             */
            if(set[cur[i].state]) continue;
            /* Skip state lines depending on unsupported extensions */
            if (!gl_info->supported[cur[i].extension]) continue;
            set[cur[i].state] = TRUE;
            /* In some cases having an extension means that nothing has to be
             * done for a state, e.g. if GL_ARB_texture_non_power_of_two is
             * supported, the texture coordinate fixup can be ignored. If the
             * apply function is used, mark the state set(done above) to prevent
             * applying later lines, but do not record anything in the state
             * table
             */
            if (!cur[i].content.representative) continue;

            handlers = num_handlers(multistate_funcs[cur[i].state]);
            multistate_funcs[cur[i].state][handlers] = cur[i].content.apply;
            switch(handlers) {
                case 0:
                    StateTable[cur[i].state].apply = cur[i].content.apply;
                    break;
                case 1:
                    StateTable[cur[i].state].apply = multistate_apply_2;
                    if (!(dev_multistate_funcs[cur[i].state] = heap_calloc(2, sizeof(**dev_multistate_funcs))))
                        goto out_of_mem;

                    dev_multistate_funcs[cur[i].state][0] = multistate_funcs[cur[i].state][0];
                    dev_multistate_funcs[cur[i].state][1] = multistate_funcs[cur[i].state][1];
                    break;
                case 2:
                    StateTable[cur[i].state].apply = multistate_apply_3;
                    if (!(funcs_array = heap_realloc(dev_multistate_funcs[cur[i].state],
                            sizeof(**dev_multistate_funcs) * 3)))
                        goto out_of_mem;

                    dev_multistate_funcs[cur[i].state] = funcs_array;
                    dev_multistate_funcs[cur[i].state][2] = multistate_funcs[cur[i].state][2];
                    break;
                default:
                    ERR("Unexpected amount of state handlers for state %u: %u\n",
                        cur[i].state, handlers + 1);
            }

            if (StateTable[cur[i].state].representative
                    && StateTable[cur[i].state].representative != cur[i].content.representative)
            {
                FIXME("State %s (%#x) has different representatives in different pipeline parts.\n",
                        debug_d3dstate(cur[i].state), cur[i].state);
            }
            StateTable[cur[i].state].representative = cur[i].content.representative;
        }
    }

    prune_invalid_states(StateTable, gl_info, d3d_info);
    validate_state_table(StateTable);

    return WINED3D_OK;

out_of_mem:
    for (i = 0; i <= STATE_HIGHEST; ++i)
    {
        heap_free(dev_multistate_funcs[i]);
    }

    memset(dev_multistate_funcs, 0, (STATE_HIGHEST + 1)*sizeof(*dev_multistate_funcs));

    return E_OUTOFMEMORY;
}