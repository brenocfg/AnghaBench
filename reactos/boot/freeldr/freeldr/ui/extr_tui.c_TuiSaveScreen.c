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
 int /*<<< orphan*/  TextVideoBuffer ; 
 int UiScreenHeight ; 
 int UiScreenWidth ; 

VOID TuiSaveScreen(PUCHAR Buffer)
{
    PUCHAR    ScreenMemory = (PUCHAR)TextVideoBuffer;
    ULONG    i;

    for (i=0; i < (UiScreenWidth * UiScreenHeight * 2); i++)
    {
        Buffer[i] = ScreenMemory[i];
    }
}