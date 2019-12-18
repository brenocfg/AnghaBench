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
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char) ; 
 int WINED3D_DATA_FLOAT ; 
 int WINED3D_DATA_INT ; 
 int WINED3D_DATA_OPAQUE ; 
 int WINED3D_DATA_RESOURCE ; 
 int WINED3D_DATA_SAMPLER ; 
 int WINED3D_DATA_UAV ; 
 int WINED3D_DATA_UINT ; 

__attribute__((used)) static enum wined3d_data_type map_data_type(char t)
{
    switch (t)
    {
        case 'f':
            return WINED3D_DATA_FLOAT;
        case 'i':
            return WINED3D_DATA_INT;
        case 'u':
            return WINED3D_DATA_UINT;
        case 'O':
            return WINED3D_DATA_OPAQUE;
        case 'R':
            return WINED3D_DATA_RESOURCE;
        case 'S':
            return WINED3D_DATA_SAMPLER;
        case 'U':
            return WINED3D_DATA_UAV;
        default:
            ERR("Invalid data type '%c'.\n", t);
            return WINED3D_DATA_FLOAT;
    }
}