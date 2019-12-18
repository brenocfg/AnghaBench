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
typedef  int /*<<< orphan*/  gdImagePtr ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageSetPixel (int /*<<< orphan*/ ,int,int,int) ; 

void gdImageFilledEllipse (gdImagePtr im, int mx, int my, int w, int h, int c)
{
	int x=0,mx1=0,mx2=0,my1=0,my2=0;
	long aq,bq,dx,dy,r,rx,ry,a,b;
	int i;
	int old_y2;

	a=w>>1;
	b=h>>1;

	for (x = mx-a; x <= mx+a; x++) {
		gdImageSetPixel(im, x, my, c);
	}

	mx1 = mx-a;my1 = my;
	mx2 = mx+a;my2 = my;

	aq = a * a;
	bq = b * b;
	dx = aq << 1;
	dy = bq << 1;
	r  = a * bq;
	rx = r << 1;
	ry = 0;
	x = a;
	old_y2=-2;
	while (x > 0){
		if (r > 0) {
			my1++;my2--;
			ry +=dx;
			r  -=ry;
		}
		if (r <= 0){
			x--;
			mx1++;mx2--;
			rx -=dy;
			r  +=rx;
		}
		if(old_y2!=my2){
			for(i=mx1;i<=mx2;i++){
				gdImageSetPixel(im,i,my1,c);
				gdImageSetPixel(im,i,my2,c);
			}
		}
		old_y2 = my2;
	}
}