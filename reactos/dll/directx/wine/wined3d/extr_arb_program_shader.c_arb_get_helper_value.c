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
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;
typedef  enum arb_helper_value { ____Placeholder_arb_helper_value } arb_helper_value ;

/* Variables and functions */
#define  ARB_0001 133 
#define  ARB_EPS 132 
#define  ARB_ONE 131 
#define  ARB_TWO 130 
#define  ARB_VS_REL_OFFSET 129 
#define  ARB_ZERO 128 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,char*,int) ; 
 int WINED3D_SHADER_TYPE_PIXEL ; 
 int WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  debug_shader_type (int) ; 

__attribute__((used)) static const char *arb_get_helper_value(enum wined3d_shader_type shader, enum arb_helper_value value)
{
    if (shader != WINED3D_SHADER_TYPE_VERTEX && shader != WINED3D_SHADER_TYPE_PIXEL)
    {
        ERR("Unsupported shader type '%s'.\n", debug_shader_type(shader));
        return "bad";
    }

    if (shader == WINED3D_SHADER_TYPE_PIXEL)
    {
        switch (value)
        {
            case ARB_ZERO: return "ps_helper_const.x";
            case ARB_ONE: return "ps_helper_const.y";
            case ARB_TWO: return "coefmul.x";
            case ARB_0001: return "ps_helper_const.xxxy";
            case ARB_EPS: return "ps_helper_const.z";
            default: break;
        }
    }
    else
    {
        switch (value)
        {
            case ARB_ZERO: return "helper_const.x";
            case ARB_ONE: return "helper_const.y";
            case ARB_TWO: return "helper_const.z";
            case ARB_EPS: return "helper_const.w";
            case ARB_0001: return "helper_const.xxxy";
            case ARB_VS_REL_OFFSET: return "rel_addr_const.y";
        }
    }
    FIXME("Unmanaged %s shader helper constant requested: %u.\n",
          shader == WINED3D_SHADER_TYPE_PIXEL ? "pixel" : "vertex", value);
    switch (value)
    {
        case ARB_ZERO: return "0.0";
        case ARB_ONE: return "1.0";
        case ARB_TWO: return "2.0";
        case ARB_0001: return "{0.0, 0.0, 0.0, 1.0}";
        case ARB_EPS: return "1e-8";
        default: return "bad";
    }
}