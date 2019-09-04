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
struct TYPE_4__ {float tessTol; } ;
typedef  TYPE_1__ NVGcontext ;

/* Variables and functions */
 float nvg__absf (float) ; 
 int /*<<< orphan*/  nvg__addPoint (TYPE_1__*,float,float,int) ; 

__attribute__((used)) static void nvg__tesselateBezier(NVGcontext* ctx,
								 float x1, float y1, float x2, float y2,
								 float x3, float y3, float x4, float y4,
								 int level, int type)
{
	float x12,y12,x23,y23,x34,y34,x123,y123,x234,y234,x1234,y1234;
	float dx,dy,d2,d3;

	if (level > 10) return;

	x12 = (x1+x2)*0.5f;
	y12 = (y1+y2)*0.5f;
	x23 = (x2+x3)*0.5f;
	y23 = (y2+y3)*0.5f;
	x34 = (x3+x4)*0.5f;
	y34 = (y3+y4)*0.5f;
	x123 = (x12+x23)*0.5f;
	y123 = (y12+y23)*0.5f;

	dx = x4 - x1;
	dy = y4 - y1;
	d2 = nvg__absf(((x2 - x4) * dy - (y2 - y4) * dx));
	d3 = nvg__absf(((x3 - x4) * dy - (y3 - y4) * dx));

	if ((d2 + d3)*(d2 + d3) < ctx->tessTol * (dx*dx + dy*dy)) {
		nvg__addPoint(ctx, x4, y4, type);
		return;
	}

/*	if (nvg__absf(x1+x3-x2-x2) + nvg__absf(y1+y3-y2-y2) + nvg__absf(x2+x4-x3-x3) + nvg__absf(y2+y4-y3-y3) < ctx->tessTol) {
		nvg__addPoint(ctx, x4, y4, type);
		return;
	}*/

	x234 = (x23+x34)*0.5f;
	y234 = (y23+y34)*0.5f;
	x1234 = (x123+x234)*0.5f;
	y1234 = (y123+y234)*0.5f;

	nvg__tesselateBezier(ctx, x1,y1, x12,y12, x123,y123, x1234,y1234, level+1, 0);
	nvg__tesselateBezier(ctx, x1234,y1234, x234,y234, x34,y34, x4,y4, level+1, type);
}