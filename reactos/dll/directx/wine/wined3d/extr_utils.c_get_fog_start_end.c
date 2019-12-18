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
struct wined3d_state {int /*<<< orphan*/ * render_states; } ;
struct wined3d_context {int fog_source; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
#define  FOGSOURCE_COORD 130 
#define  FOGSOURCE_FFP 129 
#define  FOGSOURCE_VS 128 
 float INFINITY ; 
 int /*<<< orphan*/  WINED3D_FOG_NONE ; 
 size_t WINED3D_RS_FOGEND ; 
 size_t WINED3D_RS_FOGSTART ; 
 size_t WINED3D_RS_FOGTABLEMODE ; 

void get_fog_start_end(const struct wined3d_context *context, const struct wined3d_state *state,
        float *start, float *end)
{
    union
    {
        DWORD d;
        float f;
    } tmpvalue;

    switch (context->fog_source)
    {
        case FOGSOURCE_VS:
            *start = 1.0f;
            *end = 0.0f;
            break;

        case FOGSOURCE_COORD:
            *start = 255.0f;
            *end = 0.0f;
            break;

        case FOGSOURCE_FFP:
            tmpvalue.d = state->render_states[WINED3D_RS_FOGSTART];
            *start = tmpvalue.f;
            tmpvalue.d = state->render_states[WINED3D_RS_FOGEND];
            *end = tmpvalue.f;
            /* Special handling for fog_start == fog_end. In d3d with vertex
             * fog, everything is fogged. With table fog, everything with
             * fog_coord < fog_start is unfogged, and fog_coord > fog_start
             * is fogged. Windows drivers disagree when fog_coord == fog_start. */
            if (state->render_states[WINED3D_RS_FOGTABLEMODE] == WINED3D_FOG_NONE && *start == *end)
            {
                *start = -INFINITY;
                *end = 0.0f;
            }
            break;

        default:
            /* This should not happen, context->fog_source is set in wined3d, not the app. */
            ERR("Unexpected fog coordinate source.\n");
            *start = 0.0f;
            *end = 0.0f;
    }
}