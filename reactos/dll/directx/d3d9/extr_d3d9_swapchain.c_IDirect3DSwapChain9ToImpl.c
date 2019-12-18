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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/ * LPDIRECT3DSWAPCHAIN9_INT ;
typedef  int /*<<< orphan*/ * LPDIRECT3DSWAPCHAIN9 ;

/* Variables and functions */
 int /*<<< orphan*/  Direct3DSwapChain9_INT ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpVtbl ; 

LPDIRECT3DSWAPCHAIN9_INT IDirect3DSwapChain9ToImpl(LPDIRECT3DSWAPCHAIN9 iface)
{
    if (NULL == iface)
        return NULL;

    return (LPDIRECT3DSWAPCHAIN9_INT)((ULONG_PTR)iface - FIELD_OFFSET(Direct3DSwapChain9_INT, lpVtbl));
}