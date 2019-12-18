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
typedef  enum wined3d_shader_resource_type { ____Placeholder_wined3d_shader_resource_type } wined3d_shader_resource_type ;
typedef  int BOOL ;

/* Variables and functions */
 int WINED3D_SHADER_RESOURCE_TEXTURE_2DMS ; 
 int WINED3D_SHADER_RESOURCE_TEXTURE_2DMSARRAY ; 

__attribute__((used)) static BOOL is_multisampled(enum wined3d_shader_resource_type resource_type)
{
    return resource_type == WINED3D_SHADER_RESOURCE_TEXTURE_2DMS
            || resource_type == WINED3D_SHADER_RESOURCE_TEXTURE_2DMSARRAY;
}