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
typedef  int D3DPOOL ;

/* Variables and functions */
#define  D3DPOOL_DEFAULT 131 
#define  D3DPOOL_MANAGED 130 
#define  D3DPOOL_SCRATCH 129 
#define  D3DPOOL_SYSTEMMEM 128 
 unsigned int D3DUSAGE_DYNAMIC ; 
 unsigned int WINED3D_RESOURCE_ACCESS_CPU ; 
 unsigned int WINED3D_RESOURCE_ACCESS_GPU ; 
 unsigned int WINED3D_RESOURCE_ACCESS_MAP_R ; 
 unsigned int WINED3D_RESOURCE_ACCESS_MAP_W ; 

__attribute__((used)) static inline unsigned int wined3daccess_from_d3dpool(D3DPOOL pool, unsigned int usage)
{
    switch (pool)
    {
        case D3DPOOL_DEFAULT:
            if (usage & D3DUSAGE_DYNAMIC)
                return WINED3D_RESOURCE_ACCESS_GPU | WINED3D_RESOURCE_ACCESS_MAP_R | WINED3D_RESOURCE_ACCESS_MAP_W;
            return WINED3D_RESOURCE_ACCESS_GPU;
        case D3DPOOL_MANAGED:
            return WINED3D_RESOURCE_ACCESS_GPU | WINED3D_RESOURCE_ACCESS_CPU
                    | WINED3D_RESOURCE_ACCESS_MAP_R | WINED3D_RESOURCE_ACCESS_MAP_W;
        case D3DPOOL_SYSTEMMEM:
        case D3DPOOL_SCRATCH:
            return WINED3D_RESOURCE_ACCESS_CPU | WINED3D_RESOURCE_ACCESS_MAP_R | WINED3D_RESOURCE_ACCESS_MAP_W;
        default:
            return 0;
    }
}