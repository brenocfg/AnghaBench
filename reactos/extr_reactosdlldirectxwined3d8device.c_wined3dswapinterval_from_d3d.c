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
typedef  enum wined3d_swap_interval { ____Placeholder_wined3d_swap_interval } wined3d_swap_interval ;
typedef  int DWORD ;

/* Variables and functions */
#define  D3DPRESENT_INTERVAL_DEFAULT 133 
#define  D3DPRESENT_INTERVAL_FOUR 132 
#define  D3DPRESENT_INTERVAL_IMMEDIATE 131 
#define  D3DPRESENT_INTERVAL_ONE 130 
#define  D3DPRESENT_INTERVAL_THREE 129 
#define  D3DPRESENT_INTERVAL_TWO 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int WINED3D_SWAP_INTERVAL_DEFAULT ; 
 int WINED3D_SWAP_INTERVAL_FOUR ; 
 int WINED3D_SWAP_INTERVAL_IMMEDIATE ; 
 int WINED3D_SWAP_INTERVAL_ONE ; 
 int WINED3D_SWAP_INTERVAL_THREE ; 
 int WINED3D_SWAP_INTERVAL_TWO ; 

__attribute__((used)) static enum wined3d_swap_interval wined3dswapinterval_from_d3d(DWORD interval)
{
    switch (interval)
    {
        case D3DPRESENT_INTERVAL_IMMEDIATE:
            return WINED3D_SWAP_INTERVAL_IMMEDIATE;
        case D3DPRESENT_INTERVAL_ONE:
            return WINED3D_SWAP_INTERVAL_ONE;
        case D3DPRESENT_INTERVAL_TWO:
            return WINED3D_SWAP_INTERVAL_TWO;
        case D3DPRESENT_INTERVAL_THREE:
            return WINED3D_SWAP_INTERVAL_THREE;
        case D3DPRESENT_INTERVAL_FOUR:
            return WINED3D_SWAP_INTERVAL_FOUR;
        default:
            FIXME("Unhandled presentation interval %#x.\n", interval);
        case D3DPRESENT_INTERVAL_DEFAULT:
            return WINED3D_SWAP_INTERVAL_DEFAULT;
    }
}