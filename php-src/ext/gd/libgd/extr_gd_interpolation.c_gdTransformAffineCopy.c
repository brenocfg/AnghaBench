#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdRectPtr ;
struct TYPE_22__ {int width; int x; int height; int y; } ;
typedef  TYPE_2__ gdRect ;
struct TYPE_23__ {int y; int x; } ;
typedef  TYPE_3__ gdPointF ;
typedef  scalar_t__ gdInterpolationMethod ;
typedef  TYPE_4__* gdImagePtr ;
struct TYPE_24__ {scalar_t__ interpolation_id; int** tpixels; scalar_t__ alphaBlendingFlag; } ;
struct TYPE_21__ {int x; int y; int width; int height; } ;

/* Variables and functions */
 scalar_t__ GD_BICUBIC ; 
 scalar_t__ GD_BICUBIC_FIXED ; 
 scalar_t__ GD_BILINEAR_FIXED ; 
 scalar_t__ GD_DEFAULT ; 
 int GD_FALSE ; 
 scalar_t__ GD_NEAREST_NEIGHBOUR ; 
 int GD_TRUE ; 
 int abs (int) ; 
 int /*<<< orphan*/  gdAffineApplyToPointF (TYPE_3__*,TYPE_3__*,double*) ; 
 int /*<<< orphan*/  gdAffineInvert (double*,double const*) ; 
 int /*<<< orphan*/  gdImageClipRectangle (TYPE_4__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  gdImageGetClip (TYPE_4__* const,int*,int*,int*,int*) ; 
 int gdImageSX (TYPE_4__* const) ; 
 int gdImageSY (TYPE_4__* const) ; 
 int /*<<< orphan*/  gdImageSetClip (TYPE_4__* const,int,int,int,int) ; 
 int /*<<< orphan*/  gdImageSetInterpolationMethod (TYPE_4__* const,scalar_t__) ; 
 int /*<<< orphan*/  gdImageSetPixel (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdTransformAffineBoundingBox (TYPE_1__*,double const*,TYPE_2__*) ; 
 int /*<<< orphan*/  getPixelInterpolated (TYPE_4__* const,int,int,int) ; 

int gdTransformAffineCopy(gdImagePtr dst,
		  int dst_x, int dst_y,
		  const gdImagePtr src,
		  gdRectPtr src_region,
		  const double affine[6])
{
	int c1x,c1y,c2x,c2y;
	int backclip = 0;
	int backup_clipx1, backup_clipy1, backup_clipx2, backup_clipy2;
	register int x, y, src_offset_x, src_offset_y;
	double inv[6];
	int *dst_p;
	gdPointF pt, src_pt;
	gdRect bbox;
	int end_x, end_y;
	gdInterpolationMethod interpolation_id_bak = GD_DEFAULT;

	/* These methods use special implementations */
	if (src->interpolation_id == GD_BILINEAR_FIXED || src->interpolation_id == GD_BICUBIC_FIXED || src->interpolation_id == GD_NEAREST_NEIGHBOUR) {
		interpolation_id_bak = src->interpolation_id;

		gdImageSetInterpolationMethod(src, GD_BICUBIC);
	}


	gdImageClipRectangle(src, src_region);

	if (src_region->x > 0 || src_region->y > 0
		|| src_region->width < gdImageSX(src)
		|| src_region->height < gdImageSY(src)) {
		backclip = 1;

		gdImageGetClip(src, &backup_clipx1, &backup_clipy1,
		&backup_clipx2, &backup_clipy2);

		gdImageSetClip(src, src_region->x, src_region->y,
			src_region->x + src_region->width - 1,
			src_region->y + src_region->height - 1);
	}

	if (!gdTransformAffineBoundingBox(src_region, affine, &bbox)) {
		if (backclip) {
			gdImageSetClip(src, backup_clipx1, backup_clipy1,
					backup_clipx2, backup_clipy2);
		}
		gdImageSetInterpolationMethod(src, interpolation_id_bak);
		return GD_FALSE;
	}

	gdImageGetClip(dst, &c1x, &c1y, &c2x, &c2y);

	end_x = bbox.width  + abs(bbox.x);
	end_y = bbox.height + abs(bbox.y);

	/* Get inverse affine to let us work with destination -> source */
	gdAffineInvert(inv, affine);

	src_offset_x =  src_region->x;
	src_offset_y =  src_region->y;

	if (dst->alphaBlendingFlag) {
		for (y = bbox.y; y <= end_y; y++) {
			pt.y = y + 0.5;
			for (x = 0; x <= end_x; x++) {
				pt.x = x + 0.5;
				gdAffineApplyToPointF(&src_pt, &pt, inv);
				gdImageSetPixel(dst, dst_x + x, dst_y + y, getPixelInterpolated(src, src_offset_x + src_pt.x, src_offset_y + src_pt.y, 0));
			}
		}
	} else {
		for (y = 0; y <= end_y; y++) {
			pt.y = y + 0.5 + bbox.y;
			if ((dst_y + y) < 0 || ((dst_y + y) > gdImageSY(dst) -1)) {
				continue;
			}
			dst_p = dst->tpixels[dst_y + y] + dst_x;

			for (x = 0; x <= end_x; x++) {
				pt.x = x + 0.5 + bbox.x;
				gdAffineApplyToPointF(&src_pt, &pt, inv);

				if ((dst_x + x) < 0 || (dst_x + x) > (gdImageSX(dst) - 1)) {
					break;
				}
				*(dst_p++) = getPixelInterpolated(src, src_offset_x + src_pt.x, src_offset_y + src_pt.y, -1);
			}
		}
	}

	/* Restore clip if required */
	if (backclip) {
		gdImageSetClip(src, backup_clipx1, backup_clipy1,
				backup_clipx2, backup_clipy2);
	}

	gdImageSetInterpolationMethod(src, interpolation_id_bak);
	return GD_TRUE;
}