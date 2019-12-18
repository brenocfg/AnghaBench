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
typedef  int BOOL ;

/* Variables and functions */
 unsigned int WINED3D_RESOURCE_ACCESS_CPU ; 
 unsigned int WINED3D_RESOURCE_ACCESS_GPU ; 

__attribute__((used)) static inline BOOL wined3d_resource_access_is_managed(unsigned int access)
{
    return !(~access & (WINED3D_RESOURCE_ACCESS_GPU | WINED3D_RESOURCE_ACCESS_CPU));
}