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
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_4__ {int /*<<< orphan*/ ** tpixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLEND_COLOR (int,int,int,int) ; 
 int /*<<< orphan*/  gdAlphaOpaque ; 
 int gdImageGetPixel (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gdTrueColorAlpha (int,int,int,int /*<<< orphan*/ ) ; 
 int gdTrueColorGetBlue (int) ; 
 int gdTrueColorGetGreen (int) ; 
 int gdTrueColorGetRed (int) ; 

__attribute__((used)) inline static void gdImageSetAAPixelColor(gdImagePtr im, int x, int y, int color, int t)
{
	int dr,dg,db,p,r,g,b;
	dr = gdTrueColorGetRed(color);
	dg = gdTrueColorGetGreen(color);
	db = gdTrueColorGetBlue(color);

	p = gdImageGetPixel(im,x,y);
	r = gdTrueColorGetRed(p);
	g = gdTrueColorGetGreen(p);
	b = gdTrueColorGetBlue(p);

	BLEND_COLOR(t, dr, r, dr);
	BLEND_COLOR(t, dg, g, dg);
	BLEND_COLOR(t, db, b, db);
	im->tpixels[y][x]=gdTrueColorAlpha(dr, dg, db,  gdAlphaOpaque);
}