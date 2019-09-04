#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_6__ {int X; int Y; } ;
struct TYPE_8__ {TYPE_1__ dwSize; } ;
struct TYPE_7__ {scalar_t__ Y; scalar_t__ X; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ COORD ;
typedef  TYPE_3__ CONSOLE_SCREEN_BUFFER_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FillConsoleOutputAttribute (int /*<<< orphan*/ ,int,int,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SetConsoleTextAttribute (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 

BOOL ConSetScreenColor(HANDLE hOutput, WORD wColor, BOOL bFill)
{
    DWORD dwWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD coPos;

    /* Foreground and Background colors can't be the same */
    if ((wColor & 0x0F) == (wColor & 0xF0) >> 4)
        return FALSE;

    /* Fill the whole background if needed */
    if (bFill)
    {
        GetConsoleScreenBufferInfo(hOutput, &csbi);

        coPos.X = 0;
        coPos.Y = 0;
        FillConsoleOutputAttribute(hOutput,
                                   wColor & 0x00FF,
                                   csbi.dwSize.X * csbi.dwSize.Y,
                                   coPos,
                                   &dwWritten);
    }

    /* Set the text attribute */
    SetConsoleTextAttribute(hOutput, wColor & 0x00FF);
    return TRUE;
}