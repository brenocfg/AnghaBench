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
struct TYPE_2__ {int /*<<< orphan*/  texture_state; int /*<<< orphan*/  sampler_state; } ;
struct tss_lookup {TYPE_1__ u; scalar_t__ sampler_state; } ;
struct d3d_device {int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  IDirect3DDevice7 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  size_t D3DTEXTURESTAGESTATETYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DTFG_ANISOTROPIC ; 
 int /*<<< orphan*/  D3DTFG_FLATCUBIC ; 
 int /*<<< orphan*/  D3DTFG_GAUSSIANCUBIC ; 
 int /*<<< orphan*/  D3DTFG_LINEAR ; 
 int /*<<< orphan*/  D3DTFG_POINT ; 
 int /*<<< orphan*/  D3DTFP_LINEAR ; 
 int /*<<< orphan*/  D3DTFP_NONE ; 
 int /*<<< orphan*/  D3DTFP_POINT ; 
#define  D3DTSS_MAGFILTER 135 
#define  D3DTSS_MIPFILTER 134 
 size_t D3DTSS_TEXTURETRANSFORMFLAGS ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DDERR_INVALIDPARAMS ; 
 int /*<<< orphan*/  DD_OK ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,size_t) ; 
#define  WINED3D_TEXF_ANISOTROPIC 133 
#define  WINED3D_TEXF_FLAT_CUBIC 132 
#define  WINED3D_TEXF_GAUSSIAN_CUBIC 131 
#define  WINED3D_TEXF_LINEAR 130 
#define  WINED3D_TEXF_NONE 129 
#define  WINED3D_TEXF_POINT 128 
 struct d3d_device* impl_from_IDirect3DDevice7 (int /*<<< orphan*/ *) ; 
 struct tss_lookup* tss_lookup ; 
 int /*<<< orphan*/  wined3d_device_get_sampler_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_device_get_texture_stage_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 

__attribute__((used)) static HRESULT d3d_device7_GetTextureStageState(IDirect3DDevice7 *iface,
        DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD *value)
{
    struct d3d_device *device = impl_from_IDirect3DDevice7(iface);
    const struct tss_lookup *l;

    TRACE("iface %p, stage %u, state %#x, value %p.\n",
            iface, stage, state, value);

    if (!value)
        return DDERR_INVALIDPARAMS;

    if (state > D3DTSS_TEXTURETRANSFORMFLAGS)
    {
        WARN("Invalid state %#x passed.\n", state);
        return DD_OK;
    }

    l = &tss_lookup[state];

    wined3d_mutex_lock();

    if (l->sampler_state)
    {
        *value = wined3d_device_get_sampler_state(device->wined3d_device, stage, l->u.sampler_state);

        switch (state)
        {
            /* Mipfilter is a sampler state with different values */
            case D3DTSS_MIPFILTER:
            {
                switch (*value)
                {
                    case WINED3D_TEXF_NONE:
                        *value = D3DTFP_NONE;
                        break;
                    case WINED3D_TEXF_POINT:
                        *value = D3DTFP_POINT;
                        break;
                    case WINED3D_TEXF_LINEAR:
                        *value = D3DTFP_LINEAR;
                        break;
                    default:
                        ERR("Unexpected mipfilter value %#x.\n", *value);
                        *value = D3DTFP_NONE;
                        break;
                }
                break;
            }

            /* Magfilter has slightly different values */
            case D3DTSS_MAGFILTER:
            {
                switch (*value)
                {
                    case WINED3D_TEXF_POINT:
                            *value = D3DTFG_POINT;
                            break;
                    case WINED3D_TEXF_LINEAR:
                            *value = D3DTFG_LINEAR;
                            break;
                    case WINED3D_TEXF_ANISOTROPIC:
                            *value = D3DTFG_ANISOTROPIC;
                            break;
                    case WINED3D_TEXF_FLAT_CUBIC:
                            *value = D3DTFG_FLATCUBIC;
                            break;
                    case WINED3D_TEXF_GAUSSIAN_CUBIC:
                            *value = D3DTFG_GAUSSIANCUBIC;
                            break;
                    default:
                        ERR("Unexpected wined3d mag filter value %#x.\n", *value);
                        *value = D3DTFG_POINT;
                        break;
                }
                break;
            }

            default:
                break;
        }
    }
    else
    {
        *value = wined3d_device_get_texture_stage_state(device->wined3d_device, stage, l->u.texture_state);
    }

    wined3d_mutex_unlock();

    return D3D_OK;
}