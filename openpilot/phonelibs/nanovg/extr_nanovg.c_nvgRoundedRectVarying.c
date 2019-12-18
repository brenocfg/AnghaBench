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
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 float NVG_BEZIERTO ; 
 float NVG_CLOSE ; 
 int /*<<< orphan*/  NVG_COUNTOF (float*) ; 
 int /*<<< orphan*/  NVG_KAPPA90 ; 
 float NVG_LINETO ; 
 float NVG_MOVETO ; 
 int /*<<< orphan*/  nvgRect (int /*<<< orphan*/ *,float,float,float,float) ; 
 float nvg__absf (float) ; 
 int /*<<< orphan*/  nvg__appendCommands (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ) ; 
 float nvg__minf (float,float) ; 
 float nvg__signf (float) ; 

void nvgRoundedRectVarying(NVGcontext* ctx, float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)
{
	if(radTopLeft < 0.1f && radTopRight < 0.1f && radBottomRight < 0.1f && radBottomLeft < 0.1f) {
		nvgRect(ctx, x, y, w, h);
		return;
	} else {
		float halfw = nvg__absf(w)*0.5f;
		float halfh = nvg__absf(h)*0.5f;
		float rxBL = nvg__minf(radBottomLeft, halfw) * nvg__signf(w), ryBL = nvg__minf(radBottomLeft, halfh) * nvg__signf(h);
		float rxBR = nvg__minf(radBottomRight, halfw) * nvg__signf(w), ryBR = nvg__minf(radBottomRight, halfh) * nvg__signf(h);
		float rxTR = nvg__minf(radTopRight, halfw) * nvg__signf(w), ryTR = nvg__minf(radTopRight, halfh) * nvg__signf(h);
		float rxTL = nvg__minf(radTopLeft, halfw) * nvg__signf(w), ryTL = nvg__minf(radTopLeft, halfh) * nvg__signf(h);
		float vals[] = {
			NVG_MOVETO, x, y + ryTL,
			NVG_LINETO, x, y + h - ryBL,
			NVG_BEZIERTO, x, y + h - ryBL*(1 - NVG_KAPPA90), x + rxBL*(1 - NVG_KAPPA90), y + h, x + rxBL, y + h,
			NVG_LINETO, x + w - rxBR, y + h,
			NVG_BEZIERTO, x + w - rxBR*(1 - NVG_KAPPA90), y + h, x + w, y + h - ryBR*(1 - NVG_KAPPA90), x + w, y + h - ryBR,
			NVG_LINETO, x + w, y + ryTR,
			NVG_BEZIERTO, x + w, y + ryTR*(1 - NVG_KAPPA90), x + w - rxTR*(1 - NVG_KAPPA90), y, x + w - rxTR, y,
			NVG_LINETO, x + rxTL, y,
			NVG_BEZIERTO, x + rxTL*(1 - NVG_KAPPA90), y, x, y + ryTL*(1 - NVG_KAPPA90), x, y + ryTL,
			NVG_CLOSE
		};
		nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
	}
}