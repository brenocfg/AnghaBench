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
 int /*<<< orphan*/  TuiDrawProgressBar (int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int UiScreenHeight ; 
 int UiScreenWidth ; 

VOID TuiDrawProgressBarCenter(ULONG Position, ULONG Range, PCHAR ProgressText)
{
    ULONG    Left, Top, Right, Bottom;
    ULONG    Width = 50; // Allow for 50 "bars"
    ULONG    Height = 2;

    Left = (UiScreenWidth - Width - 4) / 2;
    Right = Left + Width + 3;
    Top = (UiScreenHeight - Height - 2) / 2;
    Top += 2;
    Bottom = Top + Height + 1;

    TuiDrawProgressBar(Left, Top, Right, Bottom, Position, Range, ProgressText);
}