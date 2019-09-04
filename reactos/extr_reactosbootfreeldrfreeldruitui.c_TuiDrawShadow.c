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
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_GRAY ; 
 int /*<<< orphan*/  TextVideoBuffer ; 
 int UiScreenHeight ; 
 int UiScreenWidth ; 

VOID TuiDrawShadow(ULONG Left, ULONG Top, ULONG Right, ULONG Bottom)
{
    PUCHAR    ScreenMemory = (PUCHAR)TextVideoBuffer;
    ULONG    Idx;

    // Shade the bottom of the area
    if (Bottom < (UiScreenHeight - 1))
    {
        if (UiScreenHeight < 34)
        {
            Idx=Left + 2;
        }
        else
        {
            Idx=Left + 1;
        }

        for (; Idx<=Right; Idx++)
        {
            ScreenMemory[(((Bottom+1)*2)*UiScreenWidth)+(Idx*2)+1] = ATTR(COLOR_GRAY, COLOR_BLACK);
        }
    }

    // Shade the right of the area
    if (Right < (UiScreenWidth - 1))
    {
        for (Idx=Top+1; Idx<=Bottom; Idx++)
        {
            ScreenMemory[((Idx*2)*UiScreenWidth)+((Right+1)*2)+1] = ATTR(COLOR_GRAY, COLOR_BLACK);
        }
    }
    if (UiScreenHeight < 34)
    {
        if ((Right + 1) < (UiScreenWidth - 1))
        {
            for (Idx=Top+1; Idx<=Bottom; Idx++)
            {
                ScreenMemory[((Idx*2)*UiScreenWidth)+((Right+2)*2)+1] = ATTR(COLOR_GRAY, COLOR_BLACK);
            }
        }
    }

    // Shade the bottom right corner
    if ((Right < (UiScreenWidth - 1)) && (Bottom < (UiScreenHeight - 1)))
    {
        ScreenMemory[(((Bottom+1)*2)*UiScreenWidth)+((Right+1)*2)+1] = ATTR(COLOR_GRAY, COLOR_BLACK);
    }
    if (UiScreenHeight < 34)
    {
        if (((Right + 1) < (UiScreenWidth - 1)) && (Bottom < (UiScreenHeight - 1)))
        {
            ScreenMemory[(((Bottom+1)*2)*UiScreenWidth)+((Right+2)*2)+1] = ATTR(COLOR_GRAY, COLOR_BLACK);
        }
    }
}