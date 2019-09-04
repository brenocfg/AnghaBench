#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int dwSize; scalar_t__ bVisible; } ;
typedef  TYPE_1__ CONSOLE_CURSOR_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleCursorInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 

VOID SetCursorType(BOOL bInsert, BOOL bVisible)
{
    CONSOLE_CURSOR_INFO cci;

    cci.dwSize = bInsert ? 10 : 99;
    cci.bVisible = bVisible;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}