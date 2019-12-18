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
struct TYPE_4__ {scalar_t__ image_type; int /*<<< orphan*/ * clip; scalar_t__ image; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  int /*<<< orphan*/  GpRectF ;
typedef  TYPE_1__ GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeIntersect ; 
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  GdipCombineRegionRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCombineRegionRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 scalar_t__ ImageTypeMetafile ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  get_graphics_bounds (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GpStatus get_visible_clip_region(GpGraphics *graphics, GpRegion *rgn)
{
    GpStatus stat;
    GpRectF rectf;
    GpRegion* tmp;

    /* Ignore graphics image bounds for metafiles */
    if (graphics->image && graphics->image_type == ImageTypeMetafile)
        return GdipCombineRegionRegion(rgn, graphics->clip, CombineModeReplace);

    if((stat = get_graphics_bounds(graphics, &rectf)) != Ok)
        return stat;

    if((stat = GdipCreateRegion(&tmp)) != Ok)
        return stat;

    if((stat = GdipCombineRegionRect(tmp, &rectf, CombineModeReplace)) != Ok)
        goto end;

    if((stat = GdipCombineRegionRegion(tmp, graphics->clip, CombineModeIntersect)) != Ok)
        goto end;

    stat = GdipCombineRegionRegion(rgn, tmp, CombineModeReplace);

end:
    GdipDeleteRegion(tmp);
    return stat;
}