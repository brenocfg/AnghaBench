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
typedef  enum wined3d_channel_type { ____Placeholder_wined3d_channel_type } wined3d_channel_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char) ; 
 int WINED3D_CHANNEL_TYPE_DEPTH ; 
 int WINED3D_CHANNEL_TYPE_FLOAT ; 
 int WINED3D_CHANNEL_TYPE_NONE ; 
 int WINED3D_CHANNEL_TYPE_SINT ; 
 int WINED3D_CHANNEL_TYPE_SNORM ; 
 int WINED3D_CHANNEL_TYPE_STENCIL ; 
 int WINED3D_CHANNEL_TYPE_UINT ; 
 int WINED3D_CHANNEL_TYPE_UNORM ; 
 int WINED3D_CHANNEL_TYPE_UNUSED ; 

__attribute__((used)) static enum wined3d_channel_type map_channel_type(char t)
{
    switch (t)
    {
        case 'u':
            return WINED3D_CHANNEL_TYPE_UNORM;
        case 'i':
            return WINED3D_CHANNEL_TYPE_SNORM;
        case 'U':
            return WINED3D_CHANNEL_TYPE_UINT;
        case 'I':
            return WINED3D_CHANNEL_TYPE_SINT;
        case 'F':
            return WINED3D_CHANNEL_TYPE_FLOAT;
        case 'D':
            return WINED3D_CHANNEL_TYPE_DEPTH;
        case 'S':
            return WINED3D_CHANNEL_TYPE_STENCIL;
        case 'X':
            return WINED3D_CHANNEL_TYPE_UNUSED;
        default:
            ERR("Invalid channel type '%c'.\n", t);
            return WINED3D_CHANNEL_TYPE_NONE;
    }
}