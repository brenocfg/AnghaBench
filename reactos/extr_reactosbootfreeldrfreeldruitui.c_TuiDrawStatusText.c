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
typedef  scalar_t__ SIZE_T ;
typedef  char* PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiDrawText (int,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ UiScreenHeight ; 
 scalar_t__ UiScreenWidth ; 
 int /*<<< orphan*/  UiStatusBarBgColor ; 
 int /*<<< orphan*/  UiStatusBarFgColor ; 
 int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM () ; 
 scalar_t__ strlen (char*) ; 

VOID TuiDrawStatusText(PCSTR StatusText)
{
    SIZE_T    i;

    TuiDrawText(0, UiScreenHeight-1, " ", ATTR(UiStatusBarFgColor, UiStatusBarBgColor));
    TuiDrawText(1, UiScreenHeight-1, StatusText, ATTR(UiStatusBarFgColor, UiStatusBarBgColor));

    for (i=strlen(StatusText)+1; i<UiScreenWidth; i++)
    {
        TuiDrawText((ULONG)i, UiScreenHeight-1, " ", ATTR(UiStatusBarFgColor, UiStatusBarBgColor));
    }

    VideoCopyOffScreenBufferToVRAM();
}