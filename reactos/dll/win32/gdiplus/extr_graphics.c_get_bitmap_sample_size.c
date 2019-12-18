#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WrapMode ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_5__ {scalar_t__ Height; scalar_t__ Width; scalar_t__ Y; scalar_t__ X; } ;
typedef  scalar_t__ REAL ;
typedef  int InterpolationMode ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ GpRect ;
typedef  TYPE_2__ GpBitmap ;

/* Variables and functions */
#define  InterpolationModeBicubic 132 
#define  InterpolationModeBilinear 131 
#define  InterpolationModeHighQualityBicubic 130 
#define  InterpolationModeHighQualityBilinear 129 
#define  InterpolationModeNearestNeighbor 128 
 scalar_t__ WrapModeClamp ; 
 int /*<<< orphan*/  ceilf (scalar_t__) ; 
 int /*<<< orphan*/  floorf (scalar_t__) ; 
 scalar_t__ gdip_round (scalar_t__) ; 

__attribute__((used)) static void get_bitmap_sample_size(InterpolationMode interpolation, WrapMode wrap,
    GpBitmap* bitmap, REAL srcx, REAL srcy, REAL srcwidth, REAL srcheight,
    GpRect *rect)
{
    INT left, top, right, bottom;

    switch (interpolation)
    {
    case InterpolationModeHighQualityBilinear:
    case InterpolationModeHighQualityBicubic:
    /* FIXME: Include a greater range for the prefilter? */
    case InterpolationModeBicubic:
    case InterpolationModeBilinear:
        left = (INT)(floorf(srcx));
        top = (INT)(floorf(srcy));
        right = (INT)(ceilf(srcx+srcwidth));
        bottom = (INT)(ceilf(srcy+srcheight));
        break;
    case InterpolationModeNearestNeighbor:
    default:
        left = gdip_round(srcx);
        top = gdip_round(srcy);
        right = gdip_round(srcx+srcwidth);
        bottom = gdip_round(srcy+srcheight);
        break;
    }

    if (wrap == WrapModeClamp)
    {
        if (left < 0)
            left = 0;
        if (top < 0)
            top = 0;
        if (right >= bitmap->width)
            right = bitmap->width-1;
        if (bottom >= bitmap->height)
            bottom = bitmap->height-1;
        if (bottom < top || right < left)
            /* entirely outside image, just sample a pixel so we don't have to
             * special-case this later */
            left = top = right = bottom = 0;
    }
    else
    {
        /* In some cases we can make the rectangle smaller here, but the logic
         * is hard to get right, and tiling suggests we're likely to use the
         * entire source image. */
        if (left < 0 || right >= bitmap->width)
        {
            left = 0;
            right = bitmap->width-1;
        }

        if (top < 0 || bottom >= bitmap->height)
        {
            top = 0;
            bottom = bitmap->height-1;
        }
    }

    rect->X = left;
    rect->Y = top;
    rect->Width = right - left + 1;
    rect->Height = bottom - top + 1;
}