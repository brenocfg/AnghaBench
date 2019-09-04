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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_DEFAULT ; 
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_FOUR ; 
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_IMMEDIATE ; 
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_ONE ; 
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_THREE ; 
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_TWO ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  WINED3D_SWAP_INTERVAL_DEFAULT 133 
#define  WINED3D_SWAP_INTERVAL_FOUR 132 
#define  WINED3D_SWAP_INTERVAL_IMMEDIATE 131 
#define  WINED3D_SWAP_INTERVAL_ONE 130 
#define  WINED3D_SWAP_INTERVAL_THREE 129 
#define  WINED3D_SWAP_INTERVAL_TWO 128 

__attribute__((used)) static DWORD d3dpresentationinterval_from_wined3dswapinterval(enum wined3d_swap_interval interval)
{
    switch (interval)
    {
        case WINED3D_SWAP_INTERVAL_IMMEDIATE:
            return D3DPRESENT_INTERVAL_IMMEDIATE;
        case WINED3D_SWAP_INTERVAL_ONE:
            return D3DPRESENT_INTERVAL_ONE;
        case WINED3D_SWAP_INTERVAL_TWO:
            return D3DPRESENT_INTERVAL_TWO;
        case WINED3D_SWAP_INTERVAL_THREE:
            return D3DPRESENT_INTERVAL_THREE;
        case WINED3D_SWAP_INTERVAL_FOUR:
            return D3DPRESENT_INTERVAL_FOUR;
        default:
            ERR("Invalid swap interval %#x.\n", interval);
        case WINED3D_SWAP_INTERVAL_DEFAULT:
            return D3DPRESENT_INTERVAL_DEFAULT;
    }
}