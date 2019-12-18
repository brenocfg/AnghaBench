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
typedef  int /*<<< orphan*/  bmp ;
struct TYPE_13__ {int bmWidth; int bmHeight; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdc; scalar_t__ image; scalar_t__ hwnd; } ;
struct TYPE_11__ {int X; int Y; int Width; int Height; } ;
struct TYPE_10__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  scalar_t__ HBITMAP ;
typedef  scalar_t__ GpUnit ;
typedef  scalar_t__ GpStatus ;
typedef  TYPE_2__ GpRectF ;
typedef  TYPE_3__ GpGraphics ;
typedef  TYPE_4__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ GdipGetImageBounds (scalar_t__,TYPE_2__*,scalar_t__*) ; 
 scalar_t__ GenericError ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetCurrentObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetObjectType (int /*<<< orphan*/ ) ; 
 scalar_t__ GetObjectW (scalar_t__,int,TYPE_4__*) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  OBJ_BITMAP ; 
 scalar_t__ OBJ_MEMDC ; 
 scalar_t__ Ok ; 
 scalar_t__ UnitPixel ; 
 int /*<<< orphan*/  VERTRES ; 

__attribute__((used)) static GpStatus get_graphics_device_bounds(GpGraphics* graphics, GpRectF* rect)
{
    RECT wnd_rect;
    GpStatus stat=Ok;
    GpUnit unit;

    if(graphics->hwnd) {
        if(!GetClientRect(graphics->hwnd, &wnd_rect))
            return GenericError;

        rect->X = wnd_rect.left;
        rect->Y = wnd_rect.top;
        rect->Width = wnd_rect.right - wnd_rect.left;
        rect->Height = wnd_rect.bottom - wnd_rect.top;
    }else if (graphics->image){
        stat = GdipGetImageBounds(graphics->image, rect, &unit);
        if (stat == Ok && unit != UnitPixel)
            FIXME("need to convert from unit %i\n", unit);
    }else if (GetObjectType(graphics->hdc) == OBJ_MEMDC){
        HBITMAP hbmp;
        BITMAP bmp;

        rect->X = 0;
        rect->Y = 0;

        hbmp = GetCurrentObject(graphics->hdc, OBJ_BITMAP);
        if (hbmp && GetObjectW(hbmp, sizeof(bmp), &bmp))
        {
            rect->Width = bmp.bmWidth;
            rect->Height = bmp.bmHeight;
        }
        else
        {
            /* FIXME: ??? */
            rect->Width = 1;
            rect->Height = 1;
        }
    }else{
        rect->X = 0;
        rect->Y = 0;
        rect->Width = GetDeviceCaps(graphics->hdc, HORZRES);
        rect->Height = GetDeviceCaps(graphics->hdc, VERTRES);
    }

    return stat;
}