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
 int /*<<< orphan*/  MiniTuiDrawProgressBar (int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int UiScreenHeight ; 

VOID MiniTuiDrawProgressBarCenter(ULONG Position, ULONG Range, PCHAR ProgressText)
{
    ULONG        Left, Top, Right, Bottom;
    ULONG        Width = 50; // Allow for 50 "bars"
    ULONG        Height = 2;

    Width = 80;
    Left = 0;
    Right = Left + Width;
    Top = UiScreenHeight - Height - 4;
    Bottom = Top + Height + 1;

    MiniTuiDrawProgressBar(Left, Top, Right, Bottom, Position, Range, ProgressText);
}