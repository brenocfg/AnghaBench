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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ int32 ;
struct TYPE_3__ {float Y0; float X0; float Z0; } ;
typedef  TYPE_1__ TIFFCIELabToRGB ;

/* Variables and functions */

void
TIFFCIELabToXYZ(TIFFCIELabToRGB *cielab, uint32 l, int32 a, int32 b,
		float *X, float *Y, float *Z)
{
	float L = (float)l * 100.0F / 255.0F;
	float cby, tmp;

	if( L < 8.856F ) {
		*Y = (L * cielab->Y0) / 903.292F;
		cby = 7.787F * (*Y / cielab->Y0) + 16.0F / 116.0F;
	} else {
		cby = (L + 16.0F) / 116.0F;
		*Y = cielab->Y0 * cby * cby * cby;
	}

	tmp = (float)a / 500.0F + cby;
	if( tmp < 0.2069F )
		*X = cielab->X0 * (tmp - 0.13793F) / 7.787F;
	else    
		*X = cielab->X0 * tmp * tmp * tmp;

	tmp = cby - (float)b / 200.0F;
	if( tmp < 0.2069F )
		*Z = cielab->Z0 * (tmp - 0.13793F) / 7.787F;
	else    
		*Z = cielab->Z0 * tmp * tmp * tmp;
}