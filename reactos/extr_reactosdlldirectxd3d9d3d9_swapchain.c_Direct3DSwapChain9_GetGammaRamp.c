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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  GammaRamp; } ;
typedef  TYPE_1__ Direct3DSwapChain9_INT ;
typedef  int /*<<< orphan*/  D3DGAMMARAMP ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

VOID Direct3DSwapChain9_GetGammaRamp(Direct3DSwapChain9_INT* pThisSwapChain, D3DGAMMARAMP* pRamp)
{
    memcpy(pRamp, &pThisSwapChain->GammaRamp, sizeof(D3DGAMMARAMP));
}