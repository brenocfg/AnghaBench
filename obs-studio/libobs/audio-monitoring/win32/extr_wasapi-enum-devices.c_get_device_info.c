#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int (* obs_enum_audio_device_cb ) (void*,char*,char*) ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_21__ {TYPE_1__* lpVtbl; } ;
struct TYPE_20__ {TYPE_2__* lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * pwszVal; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* GetValue ) (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ;int /*<<< orphan*/  (* OpenPropertyStore ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_4__**) ;int /*<<< orphan*/  (* GetId ) (TYPE_4__*,int /*<<< orphan*/ **) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  (* Item ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__**) ;} ;
typedef  TYPE_3__ PROPVARIANT ;
typedef  TYPE_4__ IPropertyStore ;
typedef  TYPE_5__ IMMDeviceCollection ;
typedef  TYPE_4__ IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKEY_Device_FriendlyName ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_3__*) ; 
 int /*<<< orphan*/  STGM_READ ; 
 int /*<<< orphan*/  os_wcs_to_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  safe_release (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static bool get_device_info(obs_enum_audio_device_cb cb, void *data,
			    IMMDeviceCollection *collection, UINT idx)
{
	IPropertyStore *store = NULL;
	IMMDevice *device = NULL;
	PROPVARIANT name_var;
	char utf8_name[512];
	WCHAR *w_id = NULL;
	char utf8_id[512];
	bool cont = true;
	HRESULT hr;

	hr = collection->lpVtbl->Item(collection, idx, &device);
	if (FAILED(hr)) {
		goto fail;
	}

	hr = device->lpVtbl->GetId(device, &w_id);
	if (FAILED(hr)) {
		goto fail;
	}

	hr = device->lpVtbl->OpenPropertyStore(device, STGM_READ, &store);
	if (FAILED(hr)) {
		goto fail;
	}

	PropVariantInit(&name_var);
	hr = store->lpVtbl->GetValue(store, &PKEY_Device_FriendlyName,
				     &name_var);
	if (FAILED(hr)) {
		goto fail;
	}

	os_wcs_to_utf8(w_id, 0, utf8_id, 512);
	os_wcs_to_utf8(name_var.pwszVal, 0, utf8_name, 512);

	cont = cb(data, utf8_name, utf8_id);

fail:
	safe_release(store);
	safe_release(device);
	if (w_id)
		CoTaskMemFree(w_id);
	return cont;
}