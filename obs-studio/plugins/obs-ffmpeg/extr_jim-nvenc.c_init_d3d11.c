#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct nvenc_data {int /*<<< orphan*/ * context; int /*<<< orphan*/ * device; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_14__ {TYPE_1__* lpVtbl; } ;
struct TYPE_13__ {TYPE_2__* lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* Release ) (TYPE_3__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* Release ) (TYPE_4__*) ;int /*<<< orphan*/  (* EnumAdapters ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__**) ;} ;
typedef  int /*<<< orphan*/  (* PFN_D3D11_CREATE_DEVICE ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;
typedef  TYPE_4__ IDXGIFactory1 ;
typedef  TYPE_3__ IDXGIAdapter ;
typedef  int /*<<< orphan*/  ID3D11DeviceContext ;
typedef  int /*<<< orphan*/  ID3D11Device ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  (* CREATEDXGIFACTORY1PROC ) (int /*<<< orphan*/ *,TYPE_4__**) ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_SDK_VERSION ; 
 int /*<<< orphan*/  D3D_DRIVER_TYPE_UNKNOWN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IID_IDXGIFactory1 ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_hr (char*) ; 
 int /*<<< orphan*/  get_lib (struct nvenc_data*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 

__attribute__((used)) static bool init_d3d11(struct nvenc_data *enc, obs_data_t *settings)
{
	HMODULE dxgi = get_lib(enc, "DXGI.dll");
	HMODULE d3d11 = get_lib(enc, "D3D11.dll");
	CREATEDXGIFACTORY1PROC create_dxgi;
	PFN_D3D11_CREATE_DEVICE create_device;
	IDXGIFactory1 *factory;
	IDXGIAdapter *adapter;
	ID3D11Device *device;
	ID3D11DeviceContext *context;
	HRESULT hr;

	if (!dxgi || !d3d11) {
		return false;
	}

	create_dxgi = (CREATEDXGIFACTORY1PROC)GetProcAddress(
		dxgi, "CreateDXGIFactory1");
	create_device = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(
		d3d11, "D3D11CreateDevice");

	if (!create_dxgi || !create_device) {
		error("Failed to load D3D11/DXGI procedures");
		return false;
	}

	hr = create_dxgi(&IID_IDXGIFactory1, &factory);
	if (FAILED(hr)) {
		error_hr("CreateDXGIFactory1 failed");
		return false;
	}

	hr = factory->lpVtbl->EnumAdapters(factory, 0, &adapter);
	factory->lpVtbl->Release(factory);
	if (FAILED(hr)) {
		error_hr("EnumAdapters failed");
		return false;
	}

	hr = create_device(adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, 0, NULL, 0,
			   D3D11_SDK_VERSION, &device, NULL, &context);
	adapter->lpVtbl->Release(adapter);
	if (FAILED(hr)) {
		error_hr("D3D11CreateDevice failed");
		return false;
	}

	enc->device = device;
	enc->context = context;
	return true;
}