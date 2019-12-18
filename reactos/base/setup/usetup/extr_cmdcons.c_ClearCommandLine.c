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
typedef  int /*<<< orphan*/  SHORT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_ConOutChar (char) ; 
 int /*<<< orphan*/  CONSOLE_SetCursorXY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
ClearCommandLine(
    LPSTR str,
    INT maxlen,
    SHORT orgx,
    SHORT orgy)
{
    INT count;

    CONSOLE_SetCursorXY(orgx, orgy);
    for (count = 0; count < (INT)strlen(str); count++)
        CONSOLE_ConOutChar(' ');
    memset(str, 0, maxlen);
    CONSOLE_SetCursorXY(orgx, orgy);
}