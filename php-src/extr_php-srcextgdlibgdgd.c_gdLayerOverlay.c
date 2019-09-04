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

/* Variables and functions */
 int gdAlphaMax ; 
 int gdAlphaOverlayColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdBlueMax ; 
 int /*<<< orphan*/  gdGreenMax ; 
 int /*<<< orphan*/  gdRedMax ; 
 int gdTrueColorGetAlpha (int) ; 
 int /*<<< orphan*/  gdTrueColorGetBlue (int) ; 
 int /*<<< orphan*/  gdTrueColorGetGreen (int) ; 
 int /*<<< orphan*/  gdTrueColorGetRed (int) ; 

int gdLayerOverlay (int dst, int src)
{
	int a1, a2;
	a1 = gdAlphaMax - gdTrueColorGetAlpha(dst);
	a2 = gdAlphaMax - gdTrueColorGetAlpha(src);
	return ( ((gdAlphaMax - a1*a2/gdAlphaMax) << 24) +
		(gdAlphaOverlayColor( gdTrueColorGetRed(src), gdTrueColorGetRed(dst), gdRedMax ) << 16) +
		(gdAlphaOverlayColor( gdTrueColorGetGreen(src), gdTrueColorGetGreen(dst), gdGreenMax ) << 8) +
		(gdAlphaOverlayColor( gdTrueColorGetBlue(src), gdTrueColorGetBlue(dst), gdBlueMax ))
		);
}