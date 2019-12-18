#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float* rgba; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ NVGcolor ;

/* Variables and functions */
 float nvg__clampf (float,float,float) ; 

NVGcolor nvgLerpRGBA(NVGcolor c0, NVGcolor c1, float u)
{
	int i;
	float oneminu;
	NVGcolor cint = {0};

	u = nvg__clampf(u, 0.0f, 1.0f);
	oneminu = 1.0f - u;
	for( i = 0; i <4; i++ )
	{
		cint.rgba[i] = c0.rgba[i] * oneminu + c1.rgba[i] * u;
	}

	return cint;
}