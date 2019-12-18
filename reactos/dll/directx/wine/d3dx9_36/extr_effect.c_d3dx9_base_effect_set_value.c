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
#define  D3DXPT_BOOL 137 
#define  D3DXPT_FLOAT 136 
#define  D3DXPT_INT 135 
#define  D3DXPT_STRING 134 
#define  D3DXPT_TEXTURE 133 
#define  D3DXPT_TEXTURE1D 132 
#define  D3DXPT_TEXTURE2D 131 
#define  D3DXPT_TEXTURE3D 130 
#define  D3DXPT_TEXTURECUBE 129 
#define  D3DXPT_VOID 128 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debug_d3dxparameter_type (int) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_param_type_sampler (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,scalar_t__) ; 
 int /*<<< orphan*/  set_dirty (struct d3dx_parameter*) ; 
 int /*<<< orphan*/  set_string (char**,char const*) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_set_value(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, const void *data, UINT bytes)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);
    unsigned int i;

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
        switch (param->type)
        {
            case D3DXPT_TEXTURE:
            case D3DXPT_TEXTURE1D:
            case D3DXPT_TEXTURE2D:
            case D3DXPT_TEXTURE3D:
            case D3DXPT_TEXTURECUBE:
                for (i = 0; i < (param->element_count ? param->element_count : 1); ++i)
                {
                    IUnknown *old_texture = ((IUnknown **)param->data)[i];
                    IUnknown *new_texture = ((IUnknown **)data)[i];

                    if (new_texture == old_texture)
                        continue;

                    if (new_texture)
                        IUnknown_AddRef(new_texture);
                    if (old_texture)
                        IUnknown_Release(old_texture);
                }
            /* fallthrough */
            case D3DXPT_VOID:
            case D3DXPT_BOOL:
            case D3DXPT_INT:
            case D3DXPT_FLOAT:
                TRACE("Copy %u bytes.\n", param->bytes);
                memcpy(param->data, data, param->bytes);
                set_dirty(param);
                break;

            case D3DXPT_STRING:
            {
                HRESULT hr;

                set_dirty(param);
                for (i = 0; i < (param->element_count ? param->element_count : 1); ++i)
                {
                    if (FAILED(hr = set_string(&((char **)param->data)[i], ((const char **)data)[i])))
                        return hr;
                }
                break;
            }

            default:
                FIXME("Unhandled type %s.\n", debug_d3dxparameter_type(param->type));
                break;
        }

        return D3D_OK;
    }

    WARN("Invalid argument specified\n");

    return D3DERR_INVALIDCALL;
}