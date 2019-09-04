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
struct TYPE_3__ {float tessTol; float distTol; float fringeWidth; float devicePxRatio; } ;
typedef  TYPE_1__ NVGcontext ;

/* Variables and functions */

__attribute__((used)) static void nvg__setDevicePixelRatio(NVGcontext* ctx, float ratio)
{
	ctx->tessTol = 0.25f / ratio;
	ctx->distTol = 0.01f / ratio;
	ctx->fringeWidth = 1.0f / ratio;
	ctx->devicePxRatio = ratio;
}