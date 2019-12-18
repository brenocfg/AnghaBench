#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float commandx; float commandy; } ;
typedef  TYPE_1__ NVGcontext ;

/* Variables and functions */
 float NVG_BEZIERTO ; 
 int /*<<< orphan*/  NVG_COUNTOF (float*) ; 
 int /*<<< orphan*/  nvg__appendCommands (TYPE_1__*,float*,int /*<<< orphan*/ ) ; 

void nvgQuadTo(NVGcontext* ctx, float cx, float cy, float x, float y)
{
    float x0 = ctx->commandx;
    float y0 = ctx->commandy;
    float vals[] = { NVG_BEZIERTO,
        x0 + 2.0f/3.0f*(cx - x0), y0 + 2.0f/3.0f*(cy - y0),
        x + 2.0f/3.0f*(cx - x), y + 2.0f/3.0f*(cy - y),
        x, y };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}