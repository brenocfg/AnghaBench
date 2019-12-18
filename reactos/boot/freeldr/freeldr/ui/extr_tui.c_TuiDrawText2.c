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
typedef  size_t ULONG ;
typedef  scalar_t__ UCHAR ;
typedef  scalar_t__* PUCHAR ;
typedef  scalar_t__* PCSTR ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  TextVideoBuffer ; 
 size_t UiScreenWidth ; 

VOID TuiDrawText2(ULONG X, ULONG Y, ULONG MaxNumChars, PCSTR Text, UCHAR Attr)
{
    PUCHAR    ScreenMemory = (PUCHAR)TextVideoBuffer;
    ULONG    i, j;

    // Draw the text
    for (i = X, j = 0; Text[j] && i < UiScreenWidth && (MaxNumChars > 0 ? j < MaxNumChars : TRUE); i++, j++)
    {
        ScreenMemory[((Y*2)*UiScreenWidth)+(i*2)] = (UCHAR)Text[j];
        ScreenMemory[((Y*2)*UiScreenWidth)+(i*2)+1] = Attr;
    }
}