#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_5__ {TYPE_1__ BufferDesc; } ;
typedef  int /*<<< orphan*/  IDXGISwapChain ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DXGI_SWAP_CHAIN_DESC ;
typedef  int /*<<< orphan*/  DXGI_FORMAT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDXGISwapChain_GetDesc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  IDXGISwapChain_ResizeBuffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool update_swapchain_format(struct mp_log *log,
                                    IDXGISwapChain *swapchain,
                                    DXGI_FORMAT format)
{
    DXGI_SWAP_CHAIN_DESC desc;

    HRESULT hr = IDXGISwapChain_GetDesc(swapchain, &desc);
    if (FAILED(hr)) {
        mp_fatal(log, "Failed to query swap chain's current state: %s\n",
                 mp_HRESULT_to_str(hr));
        return false;
    }

    hr = IDXGISwapChain_ResizeBuffers(swapchain, 0, desc.BufferDesc.Width,
                                      desc.BufferDesc.Height,
                                      format, 0);
    if (FAILED(hr)) {
        mp_fatal(log, "Couldn't update swapchain format: %s\n",
                 mp_HRESULT_to_str(hr));
        return false;
    }

    return true;
}