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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  HKL ;

/* Variables and functions */
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 

VOID
GetLayoutIDByHkl(HKL hKl, LPTSTR szLayoutID, SIZE_T LayoutIDLength)
{
    /*
        FIXME!!! This way of getting layout ID incorrect!
                 This will not work correctly for 0001040a, 00010410, etc
    */
    StringCchPrintf(szLayoutID, LayoutIDLength, _T("%08x"), LOWORD(hKl));
}