#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ra_tex_params {int dimensions; scalar_t__ storage_dst; scalar_t__ blit_dst; scalar_t__ render_dst; scalar_t__ src_repeat; scalar_t__ src_linear; scalar_t__ render_src; int /*<<< orphan*/  format; scalar_t__ blit_src; } ;
struct ra_tex {struct ra_tex_params params; struct d3d_tex* priv; } ;
struct ra_d3d11 {scalar_t__ fl; int /*<<< orphan*/  dev; } ;
struct ra {struct ra_d3d11* priv; } ;
struct d3d_tex {int /*<<< orphan*/  uav; int /*<<< orphan*/  res; int /*<<< orphan*/  rtv; int /*<<< orphan*/  sampler; int /*<<< orphan*/  srv; int /*<<< orphan*/  array_slice; } ;
struct TYPE_16__ {int MaxAnisotropy; int /*<<< orphan*/  AddressW; int /*<<< orphan*/  AddressV; int /*<<< orphan*/  AddressU; int /*<<< orphan*/  Filter; int /*<<< orphan*/  MaxLOD; int /*<<< orphan*/  MinLOD; int /*<<< orphan*/  ComparisonFunc; } ;
struct TYPE_14__ {int MipLevels; } ;
struct TYPE_13__ {int MipLevels; } ;
struct TYPE_12__ {int MipLevels; int ArraySize; int /*<<< orphan*/  FirstArraySlice; } ;
struct TYPE_11__ {int MipLevels; } ;
struct TYPE_10__ {int MipLevels; int ArraySize; int /*<<< orphan*/  FirstArraySlice; } ;
struct TYPE_15__ {TYPE_5__ Texture3D; int /*<<< orphan*/  ViewDimension; TYPE_4__ Texture2D; TYPE_3__ Texture2DArray; TYPE_2__ Texture1D; TYPE_1__ Texture1DArray; int /*<<< orphan*/  Format; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_6__ D3D11_SHADER_RESOURCE_VIEW_DESC ;
typedef  TYPE_7__ D3D11_SAMPLER_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_COMPARISON_NEVER ; 
 int /*<<< orphan*/  D3D11_FILTER_MIN_MAG_MIP_LINEAR ; 
 int /*<<< orphan*/  D3D11_FLOAT32_MAX ; 
 int /*<<< orphan*/  D3D11_SRV_DIMENSION_TEXTURE1D ; 
 int /*<<< orphan*/  D3D11_SRV_DIMENSION_TEXTURE1DARRAY ; 
 int /*<<< orphan*/  D3D11_SRV_DIMENSION_TEXTURE2D ; 
 int /*<<< orphan*/  D3D11_SRV_DIMENSION_TEXTURE2DARRAY ; 
 int /*<<< orphan*/  D3D11_SRV_DIMENSION_TEXTURE3D ; 
 int /*<<< orphan*/  D3D11_TEXTURE_ADDRESS_CLAMP ; 
 int /*<<< orphan*/  D3D11_TEXTURE_ADDRESS_WRAP ; 
 scalar_t__ D3D_FEATURE_LEVEL_11_0 ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device_CreateRenderTargetView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_CreateSamplerState (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_CreateShaderResourceView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_CreateUnorderedAccessView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_ERR (struct ra*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmt_to_dxgi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tex_init(struct ra *ra, struct ra_tex *tex)
{
    struct ra_d3d11 *p = ra->priv;
    struct d3d_tex *tex_p = tex->priv;
    struct ra_tex_params *params = &tex->params;
    HRESULT hr;

    // A SRV is required for renderpasses and blitting, since blitting can use
    // a renderpass internally
    if (params->render_src || params->blit_src) {
        // Always specify the SRV format for simplicity. This will match the
        // texture format for textures created with tex_create, but it can be
        // different for wrapped planar video textures.
        D3D11_SHADER_RESOURCE_VIEW_DESC srvdesc = {
            .Format = fmt_to_dxgi(params->format),
        };
        switch (params->dimensions) {
        case 1:
            if (tex_p->array_slice >= 0) {
                srvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
                srvdesc.Texture1DArray.MipLevels = 1;
                srvdesc.Texture1DArray.FirstArraySlice = tex_p->array_slice;
                srvdesc.Texture1DArray.ArraySize = 1;
            } else {
                srvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
                srvdesc.Texture1D.MipLevels = 1;
            }
            break;
        case 2:
            if (tex_p->array_slice >= 0) {
                srvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
                srvdesc.Texture2DArray.MipLevels = 1;
                srvdesc.Texture2DArray.FirstArraySlice = tex_p->array_slice;
                srvdesc.Texture2DArray.ArraySize = 1;
            } else {
                srvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                srvdesc.Texture2D.MipLevels = 1;
            }
            break;
        case 3:
            // D3D11 does not have Texture3D arrays
            srvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
            srvdesc.Texture3D.MipLevels = 1;
            break;
        }
        hr = ID3D11Device_CreateShaderResourceView(p->dev, tex_p->res, &srvdesc,
                                                   &tex_p->srv);
        if (FAILED(hr)) {
            MP_ERR(ra, "Failed to create SRV: %s\n", mp_HRESULT_to_str(hr));
            goto error;
        }
    }

    // Samplers are required for renderpasses, but not blitting, since the blit
    // code uses its own point sampler
    if (params->render_src) {
        D3D11_SAMPLER_DESC sdesc = {
            .AddressU = D3D11_TEXTURE_ADDRESS_CLAMP,
            .AddressV = D3D11_TEXTURE_ADDRESS_CLAMP,
            .AddressW = D3D11_TEXTURE_ADDRESS_CLAMP,
            .ComparisonFunc = D3D11_COMPARISON_NEVER,
            .MinLOD = 0,
            .MaxLOD = D3D11_FLOAT32_MAX,
            .MaxAnisotropy = 1,
        };
        if (params->src_linear)
            sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        if (params->src_repeat) {
            sdesc.AddressU = sdesc.AddressV = sdesc.AddressW =
                D3D11_TEXTURE_ADDRESS_WRAP;
        }
        // The runtime pools sampler state objects internally, so we don't have
        // to worry about resource usage when creating one for every ra_tex
        hr = ID3D11Device_CreateSamplerState(p->dev, &sdesc, &tex_p->sampler);
        if (FAILED(hr)) {
            MP_ERR(ra, "Failed to create sampler: %s\n", mp_HRESULT_to_str(hr));
            goto error;
        }
    }

    // Like SRVs, an RTV is required for renderpass output and blitting
    if (params->render_dst || params->blit_dst) {
        hr = ID3D11Device_CreateRenderTargetView(p->dev, tex_p->res, NULL,
                                                 &tex_p->rtv);
        if (FAILED(hr)) {
            MP_ERR(ra, "Failed to create RTV: %s\n", mp_HRESULT_to_str(hr));
            goto error;
        }
    }

    if (p->fl >= D3D_FEATURE_LEVEL_11_0 && params->storage_dst) {
        hr = ID3D11Device_CreateUnorderedAccessView(p->dev, tex_p->res, NULL,
                                                    &tex_p->uav);
        if (FAILED(hr)) {
            MP_ERR(ra, "Failed to create UAV: %s\n", mp_HRESULT_to_str(hr));
            goto error;
        }
    }

    return true;
error:
    return false;
}