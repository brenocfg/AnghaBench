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
struct TYPE_4__ {float* xform; float* extent; int image; int /*<<< orphan*/  outerColor; int /*<<< orphan*/  innerColor; } ;
typedef  TYPE_1__ NVGpaint ;
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  NVG_NOTUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgRGBAf (int,int,int,float) ; 
 int /*<<< orphan*/  nvgTransformRotate (float*,float) ; 

NVGpaint nvgImagePattern(NVGcontext* ctx,
								float cx, float cy, float w, float h, float angle,
								int image, float alpha)
{
	NVGpaint p;
	NVG_NOTUSED(ctx);
	memset(&p, 0, sizeof(p));

	nvgTransformRotate(p.xform, angle);
	p.xform[4] = cx;
	p.xform[5] = cy;

	p.extent[0] = w;
	p.extent[1] = h;

	p.image = image;

	p.innerColor = p.outerColor = nvgRGBAf(1,1,1,alpha);

	return p;
}