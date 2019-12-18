#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ unit; int scale; int /*<<< orphan*/  hdc; int /*<<< orphan*/  xres; int /*<<< orphan*/  worldtrans; } ;
struct TYPE_10__ {scalar_t__ unit; int width; scalar_t__ dash; int* dashes; int /*<<< orphan*/  style; int /*<<< orphan*/  brush; int /*<<< orphan*/  numdashes; } ;
struct TYPE_9__ {double X; double Y; } ;
typedef  int REAL ;
typedef  int /*<<< orphan*/  LOGBRUSH ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  TYPE_1__ GpPointF ;
typedef  TYPE_2__ GpPen ;
typedef  TYPE_3__ GpGraphics ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CoordinateSpaceDevice ; 
 scalar_t__ DashStyleCustom ; 
 int /*<<< orphan*/  EndPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExtCreatePen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformMatrixPoints (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int MAX_DASHLEN ; 
 size_t SaveDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ UnitPixel ; 
 scalar_t__ UnitWorld ; 
 int /*<<< orphan*/  WineCoordinateSpaceGdiDevice ; 
 int /*<<< orphan*/  create_gdi_logbrush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_gdi_logbrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdip_round (int) ; 
 int /*<<< orphan*/  gdip_transform_points (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 size_t min (int /*<<< orphan*/ ,int) ; 
 int sqrt (double) ; 
 int units_to_pixels (int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT prepare_dc(GpGraphics *graphics, GpPen *pen)
{
    LOGBRUSH lb;
    HPEN gdipen;
    REAL width;
    INT save_state, i, numdashes;
    GpPointF pt[2];
    DWORD dash_array[MAX_DASHLEN];

    save_state = SaveDC(graphics->hdc);

    EndPath(graphics->hdc);

    if(pen->unit == UnitPixel){
        width = pen->width;
    }
    else{
        /* Get an estimate for the amount the pen width is affected by the world
         * transform. (This is similar to what some of the wine drivers do.) */
        pt[0].X = 0.0;
        pt[0].Y = 0.0;
        pt[1].X = 1.0;
        pt[1].Y = 1.0;
        GdipTransformMatrixPoints(&graphics->worldtrans, pt, 2);
        width = sqrt((pt[1].X - pt[0].X) * (pt[1].X - pt[0].X) +
                     (pt[1].Y - pt[0].Y) * (pt[1].Y - pt[0].Y)) / sqrt(2.0);

        width *= units_to_pixels(pen->width, pen->unit == UnitWorld ? graphics->unit : pen->unit, graphics->xres);
        width *= graphics->scale;

        pt[0].X = 0.0;
        pt[0].Y = 0.0;
        pt[1].X = 1.0;
        pt[1].Y = 1.0;
        gdip_transform_points(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceDevice, pt, 2);
        width *= sqrt((pt[1].X - pt[0].X) * (pt[1].X - pt[0].X) +
                      (pt[1].Y - pt[0].Y) * (pt[1].Y - pt[0].Y)) / sqrt(2.0);
    }

    if(pen->dash == DashStyleCustom){
        numdashes = min(pen->numdashes, MAX_DASHLEN);

        TRACE("dashes are: ");
        for(i = 0; i < numdashes; i++){
            dash_array[i] = gdip_round(width * pen->dashes[i]);
            TRACE("%d, ", dash_array[i]);
        }
        TRACE("\n and the pen style is %x\n", pen->style);

        create_gdi_logbrush(pen->brush, &lb);
        gdipen = ExtCreatePen(pen->style, gdip_round(width), &lb,
                              numdashes, dash_array);
        free_gdi_logbrush(&lb);
    }
    else
    {
        create_gdi_logbrush(pen->brush, &lb);
        gdipen = ExtCreatePen(pen->style, gdip_round(width), &lb, 0, NULL);
        free_gdi_logbrush(&lb);
    }

    SelectObject(graphics->hdc, gdipen);

    return save_state;
}