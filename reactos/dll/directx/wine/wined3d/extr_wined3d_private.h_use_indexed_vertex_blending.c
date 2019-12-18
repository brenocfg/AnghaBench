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
struct wined3d_stream_info {int use_map; } ;
struct wined3d_state {scalar_t__* render_states; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3D_FFP_BLENDINDICES ; 
 int WINED3D_FFP_BLENDWEIGHT ; 
 size_t WINED3D_RS_INDEXEDVERTEXBLENDENABLE ; 
 size_t WINED3D_RS_VERTEXBLEND ; 
 scalar_t__ WINED3D_VBF_DISABLE ; 

__attribute__((used)) static inline BOOL use_indexed_vertex_blending(const struct wined3d_state *state, const struct wined3d_stream_info *si)
{
    if (!state->render_states[WINED3D_RS_INDEXEDVERTEXBLENDENABLE])
        return FALSE;

    if (state->render_states[WINED3D_RS_VERTEXBLEND] == WINED3D_VBF_DISABLE)
        return FALSE;

    if (!(si->use_map & (1 << WINED3D_FFP_BLENDINDICES)) || !(si->use_map & (1 << WINED3D_FFP_BLENDWEIGHT)))
        return FALSE;

    return TRUE;
}