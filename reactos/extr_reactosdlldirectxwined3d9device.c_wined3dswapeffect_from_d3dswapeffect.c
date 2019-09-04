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
typedef  enum wined3d_swap_effect { ____Placeholder_wined3d_swap_effect } wined3d_swap_effect ;
typedef  int D3DSWAPEFFECT ;

/* Variables and functions */
#define  D3DSWAPEFFECT_COPY 132 
#define  D3DSWAPEFFECT_DISCARD 131 
#define  D3DSWAPEFFECT_FLIP 130 
#define  D3DSWAPEFFECT_FLIPEX 129 
#define  D3DSWAPEFFECT_OVERLAY 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int WINED3D_SWAP_EFFECT_COPY ; 
 int WINED3D_SWAP_EFFECT_DISCARD ; 
 int WINED3D_SWAP_EFFECT_FLIP_SEQUENTIAL ; 
 int WINED3D_SWAP_EFFECT_OVERLAY ; 
 int WINED3D_SWAP_EFFECT_SEQUENTIAL ; 

__attribute__((used)) static enum wined3d_swap_effect wined3dswapeffect_from_d3dswapeffect(D3DSWAPEFFECT effect)
{
    switch (effect)
    {
        case D3DSWAPEFFECT_DISCARD:
            return WINED3D_SWAP_EFFECT_DISCARD;
        case D3DSWAPEFFECT_FLIP:
            return WINED3D_SWAP_EFFECT_SEQUENTIAL;
        case D3DSWAPEFFECT_COPY:
            return WINED3D_SWAP_EFFECT_COPY;
        case D3DSWAPEFFECT_OVERLAY:
            return WINED3D_SWAP_EFFECT_OVERLAY;
        case D3DSWAPEFFECT_FLIPEX:
            return WINED3D_SWAP_EFFECT_FLIP_SEQUENTIAL;
        default:
            FIXME("Unhandled swap effect %#x.\n", effect);
            return WINED3D_SWAP_EFFECT_SEQUENTIAL;
    }
}