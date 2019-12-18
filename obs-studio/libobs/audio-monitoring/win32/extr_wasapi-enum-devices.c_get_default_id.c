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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_14__ {TYPE_2__* lpVtbl; } ;
struct TYPE_13__ {TYPE_1__* lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* Release ) (TYPE_4__*) ;int /*<<< orphan*/  (* GetId ) (TYPE_4__*,int /*<<< orphan*/ **) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* Release ) (TYPE_3__*) ;int /*<<< orphan*/  (* GetDefaultAudioEndpoint ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**) ;} ;
typedef  TYPE_3__ IMMDeviceEnumerator ;
typedef  TYPE_4__ IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_MMDeviceEnumerator ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IMMDeviceEnumerator ; 
 char* bzalloc (int) ; 
 int /*<<< orphan*/  eConsole ; 
 int /*<<< orphan*/  eRender ; 
 int /*<<< orphan*/  os_wcs_to_utf8_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 

__attribute__((used)) static void get_default_id(char **p_id)
{
	IMMDeviceEnumerator *immde = NULL;
	IMMDevice *device = NULL;
	WCHAR *w_id = NULL;
	HRESULT hr;

	if (*p_id)
		return;

	hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL,
			      &IID_IMMDeviceEnumerator, &immde);
	if (FAILED(hr)) {
		goto fail;
	}

	hr = immde->lpVtbl->GetDefaultAudioEndpoint(immde, eRender, eConsole,
						    &device);
	if (FAILED(hr)) {
		goto fail;
	}

	hr = device->lpVtbl->GetId(device, &w_id);
	if (FAILED(hr)) {
		goto fail;
	}

	os_wcs_to_utf8_ptr(w_id, 0, p_id);

fail:
	if (!*p_id)
		*p_id = bzalloc(1);
	if (immde)
		immde->lpVtbl->Release(immde);
	if (device)
		device->lpVtbl->Release(device);
	if (w_id)
		CoTaskMemFree(w_id);
}