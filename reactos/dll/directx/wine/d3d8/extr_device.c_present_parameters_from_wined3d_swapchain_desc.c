#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_swapchain_desc {int flags; int /*<<< orphan*/  swap_interval; int /*<<< orphan*/  refresh_rate; int /*<<< orphan*/  auto_depth_stencil_format; int /*<<< orphan*/  enable_auto_depth_stencil; int /*<<< orphan*/  windowed; int /*<<< orphan*/  device_window; int /*<<< orphan*/  swap_effect; int /*<<< orphan*/  multisample_type; int /*<<< orphan*/  backbuffer_count; int /*<<< orphan*/  backbuffer_format; int /*<<< orphan*/  backbuffer_height; int /*<<< orphan*/  backbuffer_width; } ;
struct TYPE_3__ {int Flags; int /*<<< orphan*/  FullScreen_PresentationInterval; int /*<<< orphan*/  FullScreen_RefreshRateInHz; void* AutoDepthStencilFormat; int /*<<< orphan*/  EnableAutoDepthStencil; int /*<<< orphan*/  Windowed; int /*<<< orphan*/  hDeviceWindow; int /*<<< orphan*/  SwapEffect; int /*<<< orphan*/  MultiSampleType; int /*<<< orphan*/  BackBufferCount; void* BackBufferFormat; int /*<<< orphan*/  BackBufferHeight; int /*<<< orphan*/  BackBufferWidth; } ;
typedef  TYPE_1__ D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 int D3DPRESENTFLAGS_MASK ; 
 void* d3dformat_from_wined3dformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3dswapeffect_from_wined3dswapeffect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void present_parameters_from_wined3d_swapchain_desc(D3DPRESENT_PARAMETERS *present_parameters,
        const struct wined3d_swapchain_desc *swapchain_desc)
{
    present_parameters->BackBufferWidth = swapchain_desc->backbuffer_width;
    present_parameters->BackBufferHeight = swapchain_desc->backbuffer_height;
    present_parameters->BackBufferFormat = d3dformat_from_wined3dformat(swapchain_desc->backbuffer_format);
    present_parameters->BackBufferCount = swapchain_desc->backbuffer_count;
    present_parameters->MultiSampleType = swapchain_desc->multisample_type;
    present_parameters->SwapEffect = d3dswapeffect_from_wined3dswapeffect(swapchain_desc->swap_effect);
    present_parameters->hDeviceWindow = swapchain_desc->device_window;
    present_parameters->Windowed = swapchain_desc->windowed;
    present_parameters->EnableAutoDepthStencil = swapchain_desc->enable_auto_depth_stencil;
    present_parameters->AutoDepthStencilFormat
            = d3dformat_from_wined3dformat(swapchain_desc->auto_depth_stencil_format);
    present_parameters->Flags = swapchain_desc->flags & D3DPRESENTFLAGS_MASK;
    present_parameters->FullScreen_RefreshRateInHz = swapchain_desc->refresh_rate;
    present_parameters->FullScreen_PresentationInterval = swapchain_desc->swap_interval;
}