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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__* LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetFullPathName (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetRootPath (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 scalar_t__ _T (char) ; 
 int _tcslen (scalar_t__*) ; 

void getPath(TCHAR* out, LPTSTR in)
{
    if (_tcslen(in) == 2 && in[1] == _T(':'))
        GetRootPath(in,out,MAX_PATH);
    else
        GetFullPathName (in, MAX_PATH, out, NULL);
}