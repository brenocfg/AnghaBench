#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  desktop_fmt; int /*<<< orphan*/  cur_backbuf_height; int /*<<< orphan*/  cur_backbuf_width; int /*<<< orphan*/  vo; scalar_t__ opt_swap_discard; } ;
typedef  TYPE_1__ d3d_priv ;
struct TYPE_7__ {int BackBufferCount; int /*<<< orphan*/  EnableAutoDepthStencil; int /*<<< orphan*/  BackBufferFormat; int /*<<< orphan*/  PresentationInterval; int /*<<< orphan*/  MultiSampleType; int /*<<< orphan*/  BackBufferHeight; int /*<<< orphan*/  BackBufferWidth; int /*<<< orphan*/  hDeviceWindow; int /*<<< orphan*/  Flags; int /*<<< orphan*/  SwapEffect; int /*<<< orphan*/  Windowed; } ;
typedef  TYPE_2__ D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  D3DMULTISAMPLE_NONE ; 
 int /*<<< orphan*/  D3DPRESENTFLAG_VIDEO ; 
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_ONE ; 
 int /*<<< orphan*/  D3DSWAPEFFECT_COPY ; 
 int /*<<< orphan*/  D3DSWAPEFFECT_DISCARD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vo_w32_hwnd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_d3d_presentparams(d3d_priv *priv,
                                   D3DPRESENT_PARAMETERS *present_params)
{
    /* Prepare Direct3D initialization parameters. */
    memset(present_params, 0, sizeof(D3DPRESENT_PARAMETERS));
    present_params->Windowed               = TRUE;
    present_params->SwapEffect             =
        priv->opt_swap_discard ? D3DSWAPEFFECT_DISCARD : D3DSWAPEFFECT_COPY;
    present_params->Flags                  = D3DPRESENTFLAG_VIDEO;
    present_params->hDeviceWindow          = vo_w32_hwnd(priv->vo);
    present_params->BackBufferWidth        = priv->cur_backbuf_width;
    present_params->BackBufferHeight       = priv->cur_backbuf_height;
    present_params->MultiSampleType        = D3DMULTISAMPLE_NONE;
    present_params->PresentationInterval   = D3DPRESENT_INTERVAL_ONE;
    present_params->BackBufferFormat       = priv->desktop_fmt;
    present_params->BackBufferCount        = 1;
    present_params->EnableAutoDepthStencil = FALSE;
}