#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bt; } ;
struct TYPE_6__ {int forecol; int backcol; } ;
struct TYPE_5__ {int color; } ;
typedef  TYPE_1__ GpSolidFill ;
typedef  TYPE_2__ GpHatch ;
typedef  TYPE_3__ GpBrush ;
typedef  int BOOL ;

/* Variables and functions */
#define  BrushTypeHatchFill 131 
#define  BrushTypeLinearGradient 130 
#define  BrushTypeSolidColor 129 
#define  BrushTypeTextureFill 128 
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static BOOL brush_can_fill_path(GpBrush *brush, BOOL is_fill)
{
    switch (brush->bt)
    {
    case BrushTypeSolidColor:
    {
        if (is_fill)
            return TRUE;
        else
        {
            /* cannot draw semi-transparent colors */
            return (((GpSolidFill*)brush)->color & 0xff000000) == 0xff000000;
        }
    }
    case BrushTypeHatchFill:
    {
        GpHatch *hatch = (GpHatch*)brush;
        return ((hatch->forecol & 0xff000000) == 0xff000000) &&
               ((hatch->backcol & 0xff000000) == 0xff000000);
    }
    case BrushTypeLinearGradient:
    case BrushTypeTextureFill:
    /* Gdi32 isn't much help with these, so we should use brush_fill_pixels instead. */
    default:
        return FALSE;
    }
}