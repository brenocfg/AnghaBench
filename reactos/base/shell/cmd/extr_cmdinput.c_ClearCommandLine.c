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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursorXY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char) ; 
 scalar_t__ _tcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcsnset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static VOID
ClearCommandLine(LPTSTR str, INT maxlen, SHORT orgx, SHORT orgy)
{
    INT count;

    SetCursorXY (orgx, orgy);
    for (count = 0; count < (INT)_tcslen (str); count++)
        ConOutChar (_T(' '));
    _tcsnset (str, _T('\0'), maxlen);
    SetCursorXY (orgx, orgy);
}