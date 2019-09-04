#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* shiftlevel; scalar_t__* params; } ;
typedef  int TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int INT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int _T (int /*<<< orphan*/ ) ; 
 scalar_t__ _tcslen (scalar_t__*) ; 
 TYPE_1__* bc ; 

LPTSTR FindArg(TCHAR Char, BOOL *IsParam0)
{
    LPTSTR pp;
    INT n = Char - _T('0');

    TRACE ("FindArg: (%d)\n", n);

    if (n < 0 || n > 9)
        return NULL;

    n = bc->shiftlevel[n];
    *IsParam0 = (n == 0);
    pp = bc->params;

    /* Step up the strings till we reach the end */
    /* or the one we want */
    while (*pp && n--)
        pp += _tcslen (pp) + 1;

    return pp;
}