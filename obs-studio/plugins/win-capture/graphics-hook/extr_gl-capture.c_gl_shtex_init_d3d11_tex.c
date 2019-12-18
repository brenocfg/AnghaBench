#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  d3d11_tex; int /*<<< orphan*/  d3d11_device; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_5__ {int Count; } ;
struct TYPE_6__ {int MipLevels; int ArraySize; int BindFlags; int /*<<< orphan*/  MiscFlags; int /*<<< orphan*/  Usage; TYPE_1__ SampleDesc; int /*<<< orphan*/  Format; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  IDXGIResource ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ D3D11_TEXTURE2D_DESC ;

/* Variables and functions */
 int D3D11_BIND_RENDER_TARGET ; 
 int D3D11_BIND_SHADER_RESOURCE ; 
 int /*<<< orphan*/  D3D11_RESOURCE_MISC_SHARED ; 
 int /*<<< orphan*/  D3D11_USAGE_DEFAULT ; 
 int /*<<< orphan*/  DXGI_FORMAT_B8G8R8A8_UNORM ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUID_IDXGIResource ; 
 int /*<<< orphan*/  ID3D11Device_CreateTexture2D (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDXGIResource_GetSharedHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGIResource_Release (int /*<<< orphan*/ *) ; 
 TYPE_3__ data ; 
 int /*<<< orphan*/  hlog_hr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool gl_shtex_init_d3d11_tex(void)
{
	IDXGIResource *dxgi_res;
	HRESULT hr;

	D3D11_TEXTURE2D_DESC desc = {0};
	desc.Width = data.cx;
	desc.Height = data.cy;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	hr = ID3D11Device_CreateTexture2D(data.d3d11_device, &desc, NULL,
					  &data.d3d11_tex);
	if (FAILED(hr)) {
		hlog_hr("gl_shtex_init_d3d11_tex: failed to create texture",
			hr);
		return false;
	}

	hr = ID3D11Device_QueryInterface(data.d3d11_tex, &GUID_IDXGIResource,
					 (void **)&dxgi_res);
	if (FAILED(hr)) {
		hlog_hr("gl_shtex_init_d3d11_tex: failed to get IDXGIResource",
			hr);
		return false;
	}

	hr = IDXGIResource_GetSharedHandle(dxgi_res, &data.handle);
	IDXGIResource_Release(dxgi_res);

	if (FAILED(hr)) {
		hlog_hr("gl_shtex_init_d3d11_tex: failed to get shared handle",
			hr);
		return false;
	}

	return true;
}