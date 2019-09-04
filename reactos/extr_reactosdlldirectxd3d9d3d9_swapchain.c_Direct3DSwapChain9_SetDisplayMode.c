#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  BackBufferHeight; int /*<<< orphan*/  BackBufferWidth; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwHeight; int /*<<< orphan*/  dwWidth; } ;
typedef  TYPE_1__ Direct3DSwapChain9_INT ;
typedef  TYPE_2__ D3DPRESENT_PARAMETERS ;

/* Variables and functions */

VOID Direct3DSwapChain9_SetDisplayMode(Direct3DSwapChain9_INT* pThisSwapChain, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    pThisSwapChain->dwWidth = pPresentationParameters->BackBufferWidth;
    pThisSwapChain->dwHeight = pPresentationParameters->BackBufferHeight;
}