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
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiDrawCenteredText (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiDrawText (int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TuiUpdateDateTime () ; 
 int /*<<< orphan*/  UiMenuBgColor ; 
 int UiTextColor ; 
 int /*<<< orphan*/  UiTruncateStringEllipsis (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM () ; 

VOID MiniTuiDrawProgressBar(ULONG Left, ULONG Top, ULONG Right, ULONG Bottom, ULONG Position, ULONG Range, PCHAR ProgressText)
{
    ULONG        i;
    ULONG        ProgressBarWidth = (Right - Left) - 3;

    // First make sure the progress bar text fits
    UiTruncateStringEllipsis(ProgressText, ProgressBarWidth - 4);

    if (Position > Range)
    {
        Position = Range;
    }

    //
    //  Draw the "Loading..." text
    //
    TuiDrawCenteredText(Left + 2, Top + 1, Right - 2, Top + 1, ProgressText, ATTR(7, 0));

    // Draw the percent complete
    for (i=0; i<(Position*ProgressBarWidth)/Range; i++)
    {
        TuiDrawText(Left+2+i, Top+2, "\xDB", ATTR(UiTextColor, UiMenuBgColor));
    }

    TuiUpdateDateTime();
    VideoCopyOffScreenBufferToVRAM();
}