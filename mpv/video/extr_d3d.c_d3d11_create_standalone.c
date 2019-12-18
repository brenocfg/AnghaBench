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
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
struct hwcontext_create_dev_params {int dummy; } ;
struct AVBufferRef {int dummy; } ;
typedef  int /*<<< orphan*/  ID3D11Device ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  struct AVBufferRef AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_CREATE_DEVICE_VIDEO_SUPPORT ; 
 int /*<<< orphan*/  D3D11_SDK_VERSION ; 
 int /*<<< orphan*/  D3D_DRIVER_TYPE_HARDWARE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d11_D3D11CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct AVBufferRef* d3d11_wrap_device_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d_load_dlls () ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,...) ; 

__attribute__((used)) static struct AVBufferRef *d3d11_create_standalone(struct mpv_global *global,
        struct mp_log *plog, struct hwcontext_create_dev_params *params)
{
    ID3D11Device *device = NULL;
    HRESULT hr;

    d3d_load_dlls();
    if (!d3d11_D3D11CreateDevice) {
        mp_err(plog, "Failed to load D3D11 library\n");
        return NULL;
    }

    hr = d3d11_D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
                                 D3D11_CREATE_DEVICE_VIDEO_SUPPORT, NULL, 0,
                                 D3D11_SDK_VERSION, &device, NULL, NULL);
    if (FAILED(hr)) {
        mp_err(plog, "Failed to create D3D11 Device: %s\n",
               mp_HRESULT_to_str(hr));
        return NULL;
    }

    AVBufferRef *avref = d3d11_wrap_device_ref(device);
    ID3D11Device_Release(device);
    if (!avref)
        mp_err(plog, "Failed to allocate AVHWDeviceContext.\n");

    return avref;
}