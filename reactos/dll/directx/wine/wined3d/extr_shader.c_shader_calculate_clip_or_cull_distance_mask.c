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
struct wined3d_shader_signature_element {int semantic_idx; int mask; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int MAX_CLIP_DISTANCES ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  WINED3DERR_INVALIDCALL ; 
 int WINED3DSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  WINED3D_OK ; 

__attribute__((used)) static HRESULT shader_calculate_clip_or_cull_distance_mask(
        const struct wined3d_shader_signature_element *e, unsigned int *mask)
{
    /* Clip and cull distances are packed in 4 component registers. 0 and 1 are
     * the only allowed semantic indices.
     */
    if (e->semantic_idx >= MAX_CLIP_DISTANCES / 4)
    {
        *mask = 0;
        WARN("Invalid clip/cull distance index %u.\n", e->semantic_idx);
        return WINED3DERR_INVALIDCALL;
    }

    *mask = (e->mask & WINED3DSP_WRITEMASK_ALL) << (4 * e->semantic_idx);
    return WINED3D_OK;
}