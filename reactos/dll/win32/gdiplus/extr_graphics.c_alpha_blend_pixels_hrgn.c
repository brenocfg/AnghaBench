#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  hdc; TYPE_2__* image; } ;
struct TYPE_16__ {int left; int top; int right; int bottom; } ;
struct TYPE_13__ {size_t nCount; } ;
struct TYPE_15__ {TYPE_1__ rdh; scalar_t__ Buffer; } ;
struct TYPE_14__ {scalar_t__ type; } ;
typedef  TYPE_3__ RGNDATA ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  PixelFormat ;
typedef  int INT ;
typedef  scalar_t__ HRGN ;
typedef  scalar_t__ GpStatus ;
typedef  TYPE_5__ GpGraphics ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ExtSelectClipRgn (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int GetRegionData (scalar_t__,int,TYPE_3__*) ; 
 scalar_t__ ImageTypeBitmap ; 
 scalar_t__ ImageTypeMetafile ; 
 scalar_t__ NotImplemented ; 
 scalar_t__ Ok ; 
 scalar_t__ OutOfMemory ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  RGN_COPY ; 
 int /*<<< orphan*/  RestoreDC (int /*<<< orphan*/ ,int) ; 
 int SaveDC (int /*<<< orphan*/ ) ; 
 scalar_t__ alpha_blend_bmp_pixels (TYPE_5__*,int,int,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ alpha_blend_hdc_pixels (TYPE_5__*,int,int,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_clip_hrgn (TYPE_5__*,scalar_t__*) ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 

__attribute__((used)) static GpStatus alpha_blend_pixels_hrgn(GpGraphics *graphics, INT dst_x, INT dst_y,
    const BYTE *src, INT src_width, INT src_height, INT src_stride, HRGN hregion, PixelFormat fmt)
{
    GpStatus stat=Ok;

    if (graphics->image && graphics->image->type == ImageTypeBitmap)
    {
        DWORD i;
        int size;
        RGNDATA *rgndata;
        RECT *rects;
        HRGN hrgn, visible_rgn;

        hrgn = CreateRectRgn(dst_x, dst_y, dst_x + src_width, dst_y + src_height);
        if (!hrgn)
            return OutOfMemory;

        stat = get_clip_hrgn(graphics, &visible_rgn);
        if (stat != Ok)
        {
            DeleteObject(hrgn);
            return stat;
        }

        if (visible_rgn)
        {
            CombineRgn(hrgn, hrgn, visible_rgn, RGN_AND);
            DeleteObject(visible_rgn);
        }

        if (hregion)
            CombineRgn(hrgn, hrgn, hregion, RGN_AND);

        size = GetRegionData(hrgn, 0, NULL);

        rgndata = heap_alloc_zero(size);
        if (!rgndata)
        {
            DeleteObject(hrgn);
            return OutOfMemory;
        }

        GetRegionData(hrgn, size, rgndata);

        rects = (RECT*)rgndata->Buffer;

        for (i=0; stat == Ok && i<rgndata->rdh.nCount; i++)
        {
            stat = alpha_blend_bmp_pixels(graphics, rects[i].left, rects[i].top,
                &src[(rects[i].left - dst_x) * 4 + (rects[i].top - dst_y) * src_stride],
                rects[i].right - rects[i].left, rects[i].bottom - rects[i].top,
                src_stride, fmt);
        }

        heap_free(rgndata);

        DeleteObject(hrgn);

        return stat;
    }
    else if (graphics->image && graphics->image->type == ImageTypeMetafile)
    {
        ERR("This should not be used for metafiles; fix caller\n");
        return NotImplemented;
    }
    else
    {
        HRGN hrgn;
        int save;

        stat = get_clip_hrgn(graphics, &hrgn);

        if (stat != Ok)
            return stat;

        save = SaveDC(graphics->hdc);

        ExtSelectClipRgn(graphics->hdc, hrgn, RGN_COPY);

        if (hregion)
            ExtSelectClipRgn(graphics->hdc, hregion, RGN_AND);

        stat = alpha_blend_hdc_pixels(graphics, dst_x, dst_y, src, src_width,
            src_height, src_stride, fmt);

        RestoreDC(graphics->hdc, save);

        DeleteObject(hrgn);

        return stat;
    }
}