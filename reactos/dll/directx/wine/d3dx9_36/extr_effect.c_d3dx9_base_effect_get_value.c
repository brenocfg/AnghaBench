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
struct d3dx_parameter {scalar_t__ class; int type; scalar_t__ bytes; int element_count; scalar_t__ data; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 scalar_t__ D3DXPC_OBJECT ; 
#define  D3DXPT_BOOL 139 
#define  D3DXPT_FLOAT 138 
#define  D3DXPT_INT 137 
#define  D3DXPT_PIXELSHADER 136 
#define  D3DXPT_STRING 135 
#define  D3DXPT_TEXTURE 134 
#define  D3DXPT_TEXTURE1D 133 
#define  D3DXPT_TEXTURE2D 132 
#define  D3DXPT_TEXTURE3D 131 
#define  D3DXPT_TEXTURECUBE 130 
#define  D3DXPT_VERTEXSHADER 129 
#define  D3DXPT_VOID 128 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ debug_d3dxparameter_type (int) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_param_type_sampler (int) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_value(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, void *data, UINT bytes)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (!param)
    {
        WARN("Invalid parameter %p specified\n", parameter);
        return D3DERR_INVALIDCALL;
    }

    /* samplers don't touch data */
    if (param->class == D3DXPC_OBJECT && is_param_type_sampler(param->type))
    {
        TRACE("Sampler: returning E_FAIL\n");
        return E_FAIL;
    }

    if (data && param->bytes <= bytes)
    {
        TRACE("Type %s\n", debug_d3dxparameter_type(param->type));

        switch (param->type)
        {
            case D3DXPT_VOID:
            case D3DXPT_BOOL:
            case D3DXPT_INT:
            case D3DXPT_FLOAT:
            case D3DXPT_STRING:
                break;

            case D3DXPT_VERTEXSHADER:
            case D3DXPT_PIXELSHADER:
            case D3DXPT_TEXTURE:
            case D3DXPT_TEXTURE1D:
            case D3DXPT_TEXTURE2D:
            case D3DXPT_TEXTURE3D:
            case D3DXPT_TEXTURECUBE:
            {
                UINT i;

                for (i = 0; i < (param->element_count ? param->element_count : 1); ++i)
                {
                    IUnknown *unk = ((IUnknown **)param->data)[i];
                    if (unk) IUnknown_AddRef(unk);
                }
                break;
            }

            default:
                FIXME("Unhandled type %s\n", debug_d3dxparameter_type(param->type));
                break;
        }

        TRACE("Copy %u bytes\n", param->bytes);
        memcpy(data, param->data, param->bytes);
        return D3D_OK;
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}