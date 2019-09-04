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
struct TYPE_3__ {float R; float G; float B; } ;
typedef  TYPE_1__ RGBType ;
typedef  int /*<<< orphan*/  HWBType ;

/* Variables and functions */
 int HWB_UNDEFINED ; 
 float MAX3 (float,float,float) ; 
 float MIN3 (float,float,float) ; 
 int /*<<< orphan*/  RETURN_HWB (int,float,float) ; 

__attribute__((used)) static HWBType * RGB_to_HWB (RGBType RGB, HWBType * HWB)
{
	/*
	 * RGB are each on [0, 1]. W and B are returned on [0, 1] and H is
	 * returned on [0, 6]. Exception: H is returned UNDEFINED if W == 1 - B.
	 */

	float R = RGB.R, G = RGB.G, B = RGB.B, w, v, b, f;
	int i;

	w = MIN3 (R, G, B);
	v = MAX3 (R, G, B);
	b = 1 - v;
	if (v == w) {
		RETURN_HWB(HWB_UNDEFINED, w, b);
	}
	f = (R == w) ? G - B : ((G == w) ? B - R : R - G);
	i = (R == w) ? 3 : ((G == w) ? 5 : 1);

	RETURN_HWB(i - f / (v - w), w, b);
}