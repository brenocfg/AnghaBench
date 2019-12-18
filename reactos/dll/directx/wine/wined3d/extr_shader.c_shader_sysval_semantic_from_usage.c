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
typedef  enum wined3d_sysval_semantic { ____Placeholder_wined3d_sysval_semantic } wined3d_sysval_semantic ;
typedef  enum wined3d_decl_usage { ____Placeholder_wined3d_decl_usage } wined3d_decl_usage ;

/* Variables and functions */
#define  WINED3D_DECL_USAGE_POSITION 128 
 int WINED3D_SV_POSITION ; 

__attribute__((used)) static enum wined3d_sysval_semantic shader_sysval_semantic_from_usage(enum wined3d_decl_usage usage)
{
    switch (usage)
    {
        case WINED3D_DECL_USAGE_POSITION:
            return WINED3D_SV_POSITION;
        default:
            return 0;
    }
}