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
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_3__ {unsigned char trueColor; scalar_t__* alpha; scalar_t__* blue; scalar_t__* green; scalar_t__* red; int /*<<< orphan*/  transparent; int /*<<< orphan*/  colorsTotal; } ;

/* Variables and functions */
 int gdMaxColors ; 
 int /*<<< orphan*/  gdPutC (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdPutInt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdPutWord (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void _gdPutColors (gdImagePtr im, gdIOCtx * out)
{
	int i;

	gdPutC(im->trueColor, out);
	if (!im->trueColor) {
		gdPutWord(im->colorsTotal, out);
	}
	gdPutInt(im->transparent, out);
	if (!im->trueColor) {
		for (i = 0; i < gdMaxColors; i++) {
			gdPutC((unsigned char) im->red[i], out);
			gdPutC((unsigned char) im->green[i], out);
			gdPutC((unsigned char) im->blue[i], out);
			gdPutC((unsigned char) im->alpha[i], out);
		}
	}
}