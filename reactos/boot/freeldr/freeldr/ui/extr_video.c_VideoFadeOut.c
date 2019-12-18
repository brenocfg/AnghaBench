#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  MachVideoGetPaletteColor (scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  MachVideoSetPaletteColor (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MachVideoSync () ; 
 scalar_t__ RGB_MAX ; 
 scalar_t__ RGB_MAX_PER_ITERATION ; 

VOID VideoFadeOut(ULONG ColorCount)
{
    ULONG Index;
    UCHAR Color;
    UCHAR Red;
    UCHAR Green;
    UCHAR Blue;

    for (Index = 0; Index < RGB_MAX; Index++)
    {
        for (Color = 0; Color < ColorCount; Color++)
        {
            if ((Color % RGB_MAX_PER_ITERATION) == 0)
            {
                MachVideoSync();
            }

            MachVideoGetPaletteColor(Color, &Red, &Green, &Blue);

            if (Red > 0)
            {
                Red--;
            }
            if (Green > 0)
            {
                Green--;
            }
            if (Blue > 0)
            {
                Blue--;
            }

            MachVideoSetPaletteColor(Color, Red, Green, Blue);
        }
    }
}