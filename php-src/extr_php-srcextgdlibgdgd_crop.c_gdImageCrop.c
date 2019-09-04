#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdRectPtr ;
typedef  TYPE_2__* gdImagePtr ;
struct TYPE_13__ {int alphaBlendingFlag; } ;
struct TYPE_12__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int gdEffectReplace ; 
 int /*<<< orphan*/  gdImageAlphaBlending (TYPE_2__*,int) ; 
 int /*<<< orphan*/  gdImageCopy (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* gdImageCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* gdImageCreateTrueColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gdImageTrueColor (TYPE_2__*) ; 

gdImagePtr gdImageCrop(gdImagePtr src, const gdRectPtr crop)
{
	gdImagePtr dst;
	int alphaBlendingFlag;

	if (gdImageTrueColor(src)) {
		dst = gdImageCreateTrueColor(crop->width, crop->height);
	} else {
		dst = gdImageCreate(crop->width, crop->height);
	}
	if (!dst) return NULL;
	alphaBlendingFlag = dst->alphaBlendingFlag;
	gdImageAlphaBlending(dst, gdEffectReplace);
	gdImageCopy(dst, src, 0, 0, crop->x, crop->y, crop->width, crop->height);
	gdImageAlphaBlending(dst, alphaBlendingFlag);

	return dst;
}