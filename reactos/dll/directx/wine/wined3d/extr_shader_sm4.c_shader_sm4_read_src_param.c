#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_sm4_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct wined3d_shader_src_param {int swizzle; TYPE_1__ reg; int /*<<< orphan*/  modifiers; } ;
typedef  enum wined3d_sm4_swizzle_type { ____Placeholder_wined3d_sm4_swizzle_type } wined3d_sm4_swizzle_type ;
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int const*,int const*) ; 
 scalar_t__ WINED3DSPR_IMMCONST ; 
 void* WINED3DSP_NOSWIZZLE ; 
 int WINED3D_SM4_SWIZZLE_MASK ; 
#define  WINED3D_SM4_SWIZZLE_NONE 130 
#define  WINED3D_SM4_SWIZZLE_SCALAR 129 
 int WINED3D_SM4_SWIZZLE_SHIFT ; 
 int WINED3D_SM4_SWIZZLE_TYPE_MASK ; 
 int WINED3D_SM4_SWIZZLE_TYPE_SHIFT ; 
#define  WINED3D_SM4_SWIZZLE_VEC4 128 
 int /*<<< orphan*/  shader_sm4_read_param (struct wined3d_sm4_data*,int const**,int const*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL shader_sm4_read_src_param(struct wined3d_sm4_data *priv, const DWORD **ptr, const DWORD *end,
        enum wined3d_data_type data_type, struct wined3d_shader_src_param *src_param)
{
    DWORD token;

    if (*ptr >= end)
    {
        WARN("Invalid ptr %p >= end %p.\n", *ptr, end);
        return FALSE;
    }
    token = **ptr;

    if (!shader_sm4_read_param(priv, ptr, end, data_type, &src_param->reg, &src_param->modifiers))
    {
        ERR("Failed to read parameter.\n");
        return FALSE;
    }

    if (src_param->reg.type == WINED3DSPR_IMMCONST)
    {
        src_param->swizzle = WINED3DSP_NOSWIZZLE;
    }
    else
    {
        enum wined3d_sm4_swizzle_type swizzle_type =
                (token & WINED3D_SM4_SWIZZLE_TYPE_MASK) >> WINED3D_SM4_SWIZZLE_TYPE_SHIFT;

        switch (swizzle_type)
        {
            case WINED3D_SM4_SWIZZLE_NONE:
                src_param->swizzle = WINED3DSP_NOSWIZZLE;
                break;

            case WINED3D_SM4_SWIZZLE_SCALAR:
                src_param->swizzle = (token & WINED3D_SM4_SWIZZLE_MASK) >> WINED3D_SM4_SWIZZLE_SHIFT;
                src_param->swizzle = (src_param->swizzle & 0x3) * 0x55;
                break;

            case WINED3D_SM4_SWIZZLE_VEC4:
                src_param->swizzle = (token & WINED3D_SM4_SWIZZLE_MASK) >> WINED3D_SM4_SWIZZLE_SHIFT;
                break;

            default:
                FIXME("Unhandled swizzle type %#x.\n", swizzle_type);
                break;
        }
    }

    return TRUE;
}