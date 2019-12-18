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
typedef  int /*<<< orphan*/  p ;
struct TYPE_4__ {float* xform; float* extent; float radius; void* outerColor; void* innerColor; int /*<<< orphan*/  feather; } ;
typedef  TYPE_1__ NVGpaint ;
typedef  int /*<<< orphan*/  NVGcontext ;
typedef  void* NVGcolor ;

/* Variables and functions */
 int /*<<< orphan*/  NVG_NOTUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvg__maxf (float,float) ; 
 float sqrtf (float) ; 

NVGpaint nvgLinearGradient(NVGcontext* ctx,
								  float sx, float sy, float ex, float ey,
								  NVGcolor icol, NVGcolor ocol)
{
	NVGpaint p;
	float dx, dy, d;
	const float large = 1e5;
	NVG_NOTUSED(ctx);
	memset(&p, 0, sizeof(p));

	// Calculate transform aligned to the line
	dx = ex - sx;
	dy = ey - sy;
	d = sqrtf(dx*dx + dy*dy);
	if (d > 0.0001f) {
		dx /= d;
		dy /= d;
	} else {
		dx = 0;
		dy = 1;
	}

	p.xform[0] = dy; p.xform[1] = -dx;
	p.xform[2] = dx; p.xform[3] = dy;
	p.xform[4] = sx - dx*large; p.xform[5] = sy - dy*large;

	p.extent[0] = large;
	p.extent[1] = large + d*0.5f;

	p.radius = 0.0f;

	p.feather = nvg__maxf(1.0f, d);

	p.innerColor = icol;
	p.outerColor = ocol;

	return p;
}