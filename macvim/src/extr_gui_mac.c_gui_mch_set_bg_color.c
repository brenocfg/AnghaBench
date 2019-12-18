#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guicolor_T ;
struct TYPE_3__ {int red; int green; int blue; } ;
typedef  TYPE_1__ RGBColor ;

/* Variables and functions */
 int Blue (int /*<<< orphan*/ ) ; 
 int Green (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGBBackColor (TYPE_1__*) ; 
 int Red (int /*<<< orphan*/ ) ; 

void
gui_mch_set_bg_color(guicolor_T color)
{
    RGBColor TheColor;

    TheColor.red = Red(color) * 0x0101;
    TheColor.green = Green(color) * 0x0101;
    TheColor.blue = Blue(color) * 0x0101;

    RGBBackColor(&TheColor);
}