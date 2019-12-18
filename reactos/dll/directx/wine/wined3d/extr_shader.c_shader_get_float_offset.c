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
typedef  enum wined3d_shader_register_type { ____Placeholder_wined3d_shader_register_type } wined3d_shader_register_type ;
typedef  unsigned int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3DSPR_CONST 131 
#define  WINED3DSPR_CONST2 130 
#define  WINED3DSPR_CONST3 129 
#define  WINED3DSPR_CONST4 128 

__attribute__((used)) static unsigned int shader_get_float_offset(enum wined3d_shader_register_type register_type, UINT register_idx)
{
    switch (register_type)
    {
        case WINED3DSPR_CONST: return register_idx;
        case WINED3DSPR_CONST2: return 2048 + register_idx;
        case WINED3DSPR_CONST3: return 4096 + register_idx;
        case WINED3DSPR_CONST4: return 6144 + register_idx;
        default:
            FIXME("Unsupported register type: %u.\n", register_type);
            return register_idx;
    }
}