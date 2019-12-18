#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int bt; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdc; } ;
struct TYPE_11__ {int /*<<< orphan*/  color; } ;
struct TYPE_10__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_2__ GpSolidFill ;
typedef  TYPE_3__ GpGraphics ;
typedef  TYPE_4__ GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  ARGB2BMP (int /*<<< orphan*/ ) ; 
#define  BrushTypeSolidColor 128 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GenericError ; 
 int /*<<< orphan*/  GetClipBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NULLREGION ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  OutOfMemory ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  SelectClipPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_gdi_brush (TYPE_4__*) ; 
 int /*<<< orphan*/  gdi_alpha_blend (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static GpStatus brush_fill_path(GpGraphics *graphics, GpBrush *brush)
{
    GpStatus status = Ok;
    switch (brush->bt)
    {
    case BrushTypeSolidColor:
    {
        GpSolidFill *fill = (GpSolidFill*)brush;
        HBITMAP bmp = ARGB2BMP(fill->color);

        if (bmp)
        {
            RECT rc;
            /* partially transparent fill */

            if (!SelectClipPath(graphics->hdc, RGN_AND))
            {
                status = GenericError;
                DeleteObject(bmp);
                break;
            }
            if (GetClipBox(graphics->hdc, &rc) != NULLREGION)
            {
                HDC hdc = CreateCompatibleDC(NULL);

                if (!hdc)
                {
                    status = OutOfMemory;
                    DeleteObject(bmp);
                    break;
                }

                SelectObject(hdc, bmp);
                gdi_alpha_blend(graphics, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
                                hdc, 0, 0, 1, 1);
                DeleteDC(hdc);
            }

            DeleteObject(bmp);
            break;
        }
        /* else fall through */
    }
    default:
    {
        HBRUSH gdibrush, old_brush;

        gdibrush = create_gdi_brush(brush);
        if (!gdibrush)
        {
            status = OutOfMemory;
            break;
        }

        old_brush = SelectObject(graphics->hdc, gdibrush);
        FillPath(graphics->hdc);
        SelectObject(graphics->hdc, old_brush);
        DeleteObject(gdibrush);
        break;
    }
    }

    return status;
}