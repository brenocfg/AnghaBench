#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ Right; scalar_t__ Bottom; } ;
struct TYPE_6__ {scalar_t__ X; scalar_t__ Y; } ;
typedef  scalar_t__ SHORT ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;
typedef  TYPE_1__ COORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ Columns ; 
 int /*<<< orphan*/  FillConsoleOutputAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__,int*) ; 
 scalar_t__ WriteConsoleOutputCharacter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__,int*) ; 
 int /*<<< orphan*/  g_attrCurrent ; 
 TYPE_1__ g_coord ; 
 int /*<<< orphan*/  g_hConOut ; 
 TYPE_2__ g_srScrollRegion ; 
 int /*<<< orphan*/  gotoxy (scalar_t__,scalar_t__) ; 

__attribute__((used)) static BOOL
write_chars(
    LPCSTR pchBuf,
    DWORD  cchToWrite)
{
    COORD coord = g_coord;
    DWORD written;

    FillConsoleOutputAttribute(g_hConOut, g_attrCurrent, cchToWrite,
				coord, &written);
    /* When writing fails or didn't write a single character, pretend one
     * character was written, otherwise we get stuck. */
    if (WriteConsoleOutputCharacter(g_hConOut, pchBuf, cchToWrite,
				coord, &written) == 0
	    || written == 0)
	written = 1;

    g_coord.X += (SHORT) written;

    while (g_coord.X > g_srScrollRegion.Right)
    {
	g_coord.X -= (SHORT) Columns;
	if (g_coord.Y < g_srScrollRegion.Bottom)
	    g_coord.Y++;
    }

    gotoxy(g_coord.X + 1, g_coord.Y + 1);

    return written;
}