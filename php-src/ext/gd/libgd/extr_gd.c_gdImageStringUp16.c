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
typedef  int /*<<< orphan*/  gdImagePtr ;
typedef  TYPE_1__* gdFontPtr ;
struct TYPE_4__ {scalar_t__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageCharUp (int /*<<< orphan*/ ,TYPE_1__*,int,int,unsigned short,int) ; 
 int strlen16 (unsigned short*) ; 

void gdImageStringUp16 (gdImagePtr im, gdFontPtr f, int x, int y, unsigned short *s, int color)
{
	int i;
	int l;
	l = strlen16(s);
	for (i = 0; i < l; i++) {
		gdImageCharUp(im, f, x, y, s[i], color);
		y -= f->w;
	}
}