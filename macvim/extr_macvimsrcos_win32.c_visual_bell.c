#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/ * LPWORD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ COORD ;

/* Variables and functions */
 int Columns ; 
 int /*<<< orphan*/  FillConsoleOutputAttribute (int /*<<< orphan*/ ,int,int,TYPE_1__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadConsoleOutputAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__,int /*<<< orphan*/ *) ; 
 int Rows ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  WriteConsoleOutputAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc (int) ; 
 int g_attrCurrent ; 
 int /*<<< orphan*/  g_hConOut ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
visual_bell(void)
{
    COORD   coordOrigin = {0, 0};
    WORD    attrFlash = ~g_attrCurrent & 0xff;

    DWORD   dwDummy;
    LPWORD  oldattrs = (LPWORD)alloc(Rows * Columns * sizeof(WORD));

    if (oldattrs == NULL)
	return;
    ReadConsoleOutputAttribute(g_hConOut, oldattrs, Rows * Columns,
			       coordOrigin, &dwDummy);
    FillConsoleOutputAttribute(g_hConOut, attrFlash, Rows * Columns,
			       coordOrigin, &dwDummy);

    Sleep(15);	    /* wait for 15 msec */
    WriteConsoleOutputAttribute(g_hConOut, oldattrs, Rows * Columns,
				coordOrigin, &dwDummy);
    vim_free(oldattrs);
}