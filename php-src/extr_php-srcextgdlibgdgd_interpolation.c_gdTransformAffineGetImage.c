#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdRectPtr ;
struct TYPE_18__ {scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ gdRect ;
typedef  TYPE_3__* gdImagePtr ;
struct TYPE_19__ {int saveAlphaFlag; int /*<<< orphan*/  trueColor; } ;

/* Variables and functions */
 int GD_FALSE ; 
 int GD_TRUE ; 
 int /*<<< orphan*/  gdAffineConcat (double*,double const*,double*) ; 
 int /*<<< orphan*/  gdAffineTranslate (double*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gdImageAlphaBlending (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* gdImageCreateTrueColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImageDestroy (TYPE_3__*) ; 
 int /*<<< orphan*/  gdImagePaletteToTrueColor (TYPE_3__* const) ; 
 int /*<<< orphan*/  gdImageSX (TYPE_3__* const) ; 
 int /*<<< orphan*/  gdImageSY (TYPE_3__* const) ; 
 int /*<<< orphan*/  gdTransformAffineBoundingBox (TYPE_1__*,double const*,TYPE_1__*) ; 
 int gdTransformAffineCopy (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__* const,TYPE_1__*,double*) ; 

int gdTransformAffineGetImage(gdImagePtr *dst,
		  const gdImagePtr src,
		  gdRectPtr src_area,
		  const double affine[6])
{
	int res;
	double m[6];
	gdRect bbox;
	gdRect area_full;

	if (src_area == NULL) {
		area_full.x = 0;
		area_full.y = 0;
		area_full.width  = gdImageSX(src);
		area_full.height = gdImageSY(src);
		src_area = &area_full;
	}

	gdTransformAffineBoundingBox(src_area, affine, &bbox);

	*dst = gdImageCreateTrueColor(bbox.width, bbox.height);
	if (*dst == NULL) {
		return GD_FALSE;
	}
	(*dst)->saveAlphaFlag = 1;

	if (!src->trueColor) {
		gdImagePaletteToTrueColor(src);
	}

	/* Translate to dst origin (0,0) */
	gdAffineTranslate(m, -bbox.x, -bbox.y);
	gdAffineConcat(m, affine, m);

	gdImageAlphaBlending(*dst, 0);

	res = gdTransformAffineCopy(*dst,
		  0,0,
		  src,
		  src_area,
		  m);

	if (res != GD_TRUE) {
		gdImageDestroy(*dst);
		dst = NULL;
		return GD_FALSE;
	} else {
		return GD_TRUE;
	}
}