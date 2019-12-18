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
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IDXGIAdapter1 ;
typedef  int /*<<< orphan*/  IDXGIAdapter ;
typedef  int /*<<< orphan*/  ID3D11Device ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3D_FEATURE_LEVEL ;
typedef  int /*<<< orphan*/  D3D_DRIVER_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_CREATE_DEVICE_DEBUG ; 
 int /*<<< orphan*/  D3D11_SDK_VERSION ; 
 int /*<<< orphan*/  D3D_DRIVER_TYPE_HARDWARE ; 
 int /*<<< orphan*/  D3D_DRIVER_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  D3D_DRIVER_TYPE_WARP ; 
 int /*<<< orphan*/  E_FAIL ; 
 int get_feature_levels (int,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*) ; 
 int /*<<< orphan*/  pD3D11CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_device(struct mp_log *log, IDXGIAdapter1 *adapter,
                             bool warp, bool debug, int max_fl, int min_fl,
                             ID3D11Device **dev)
{
    const D3D_FEATURE_LEVEL *levels;
    int levels_len = get_feature_levels(max_fl, min_fl, &levels);
    if (!levels_len) {
        mp_fatal(log, "No suitable Direct3D feature level found\n");
        return E_FAIL;
    }

    D3D_DRIVER_TYPE type = warp ? D3D_DRIVER_TYPE_WARP
                                : D3D_DRIVER_TYPE_HARDWARE;
    UINT flags = debug ? D3D11_CREATE_DEVICE_DEBUG : 0;
    return pD3D11CreateDevice((IDXGIAdapter *)adapter, adapter ? D3D_DRIVER_TYPE_UNKNOWN : type,
                              NULL, flags, levels, levels_len, D3D11_SDK_VERSION, dev, NULL, NULL);
}