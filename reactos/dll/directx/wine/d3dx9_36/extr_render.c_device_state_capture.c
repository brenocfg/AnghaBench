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
struct device_state {unsigned int num_render_targets; int /*<<< orphan*/ * depth_stencil; int /*<<< orphan*/ ** render_targets; int /*<<< orphan*/  viewport; } ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_GetDepthStencilSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DDevice9_GetRenderTarget (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DDevice9_GetViewport (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_state_capture(IDirect3DDevice9 *device, struct device_state *state)
{
    HRESULT hr;
    unsigned int i;

    IDirect3DDevice9_GetViewport(device, &state->viewport);

    for (i = 0; i < state->num_render_targets; i++)
    {
        hr = IDirect3DDevice9_GetRenderTarget(device, i, &state->render_targets[i]);
        if (FAILED(hr)) state->render_targets[i] = NULL;
    }

    hr = IDirect3DDevice9_GetDepthStencilSurface(device, &state->depth_stencil);
    if (FAILED(hr)) state->depth_stencil = NULL;
}