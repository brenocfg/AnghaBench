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
struct IDirect3DDevice9 {int dummy; } ;
typedef  enum pres_reg_tables { ____Placeholder_pres_reg_tables } pres_reg_tables ;
typedef  int /*<<< orphan*/  ID3DXEffectStateManager ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ D3DXPARAMETER_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 scalar_t__ D3DXPT_PIXELSHADER ; 
 scalar_t__ D3DXPT_VERTEXSHADER ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
#define  PRES_REGTAB_OBCONST 130 
#define  PRES_REGTAB_OCONST 129 
#define  PRES_REGTAB_OICONST 128 
 int /*<<< orphan*/  SET_D3D_STATE_ (int /*<<< orphan*/ *,struct IDirect3DDevice9*,int /*<<< orphan*/ ,unsigned int,void*,unsigned int) ; 
 int /*<<< orphan*/  SetPixelShaderConstantB ; 
 int /*<<< orphan*/  SetPixelShaderConstantF ; 
 int /*<<< orphan*/  SetPixelShaderConstantI ; 
 int /*<<< orphan*/  SetVertexShaderConstantB ; 
 int /*<<< orphan*/  SetVertexShaderConstantF ; 
 int /*<<< orphan*/  SetVertexShaderConstantI ; 

__attribute__((used)) static HRESULT set_constants_device(ID3DXEffectStateManager *manager, struct IDirect3DDevice9 *device,
        D3DXPARAMETER_TYPE type, enum pres_reg_tables table, void *ptr,
        unsigned int start, unsigned int count)
{
    if (type == D3DXPT_VERTEXSHADER)
    {
        switch(table)
        {
            case PRES_REGTAB_OCONST:
                return SET_D3D_STATE_(manager, device, SetVertexShaderConstantF, start, ptr, count);
            case PRES_REGTAB_OICONST:
                return SET_D3D_STATE_(manager, device, SetVertexShaderConstantI, start, ptr, count);
            case PRES_REGTAB_OBCONST:
                return SET_D3D_STATE_(manager, device, SetVertexShaderConstantB, start, ptr, count);
            default:
                FIXME("Unexpected register table %u.\n", table);
                return D3DERR_INVALIDCALL;
        }
    }
    else if (type == D3DXPT_PIXELSHADER)
    {
        switch(table)
        {
            case PRES_REGTAB_OCONST:
                return SET_D3D_STATE_(manager, device, SetPixelShaderConstantF, start, ptr, count);
            case PRES_REGTAB_OICONST:
                return SET_D3D_STATE_(manager, device, SetPixelShaderConstantI, start, ptr, count);
            case PRES_REGTAB_OBCONST:
                return SET_D3D_STATE_(manager, device, SetPixelShaderConstantB, start, ptr, count);
            default:
                FIXME("Unexpected register table %u.\n", table);
                return D3DERR_INVALIDCALL;
        }
    }
    else
    {
        FIXME("Unexpected parameter type %u.\n", type);
        return D3DERR_INVALIDCALL;
    }
}