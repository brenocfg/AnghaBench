#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {size_t num; struct handle_tex* array; } ;
struct nvenc_data {TYPE_11__ input_textures; TYPE_4__* device; } ;
struct handle_tex {scalar_t__ handle; scalar_t__ member_0; int /*<<< orphan*/ * member_2; TYPE_3__* member_1; TYPE_3__* tex; int /*<<< orphan*/ * km; } ;
struct TYPE_16__ {TYPE_1__* lpVtbl; } ;
struct TYPE_15__ {TYPE_2__* lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* SetEvictionPriority ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Release ) (TYPE_3__*) ;int /*<<< orphan*/  (* QueryInterface ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* OpenSharedResource ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ;} ;
typedef  int /*<<< orphan*/  IDXGIKeyedMutex ;
typedef  TYPE_3__ ID3D11Texture2D ;
typedef  TYPE_4__ ID3D11Device ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DXGI_RESOURCE_PRIORITY_MAXIMUM ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_ID3D11Texture2D ; 
 int /*<<< orphan*/  IID_IDXGIKeyedMutex ; 
 int /*<<< orphan*/  da_push_back (TYPE_11__,struct handle_tex*) ; 
 int /*<<< orphan*/  error_hr (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ID3D11Texture2D *get_tex_from_handle(struct nvenc_data *enc,
					    uint32_t handle,
					    IDXGIKeyedMutex **km_out)
{
	ID3D11Device *device = enc->device;
	IDXGIKeyedMutex *km;
	ID3D11Texture2D *input_tex;
	HRESULT hr;

	for (size_t i = 0; i < enc->input_textures.num; i++) {
		struct handle_tex *ht = &enc->input_textures.array[i];
		if (ht->handle == handle) {
			*km_out = ht->km;
			return ht->tex;
		}
	}

	hr = device->lpVtbl->OpenSharedResource(device,
						(HANDLE)(uintptr_t)handle,
						&IID_ID3D11Texture2D,
						&input_tex);
	if (FAILED(hr)) {
		error_hr("OpenSharedResource failed");
		return NULL;
	}

	hr = input_tex->lpVtbl->QueryInterface(input_tex, &IID_IDXGIKeyedMutex,
					       &km);
	if (FAILED(hr)) {
		error_hr("QueryInterface(IDXGIKeyedMutex) failed");
		input_tex->lpVtbl->Release(input_tex);
		return NULL;
	}

	input_tex->lpVtbl->SetEvictionPriority(input_tex,
					       DXGI_RESOURCE_PRIORITY_MAXIMUM);

	*km_out = km;

	struct handle_tex new_ht = {handle, input_tex, km};
	da_push_back(enc->input_textures, &new_ht);
	return input_tex;
}