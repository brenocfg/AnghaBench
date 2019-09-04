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
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDirectory (int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetCurrentDirectory (int /*<<< orphan*/ *) ; 

BOOL IsValidPathName (LPCTSTR pszPath)
{
    TCHAR szOldPath[MAX_PATH];
    BOOL  bResult;

    GetCurrentDirectory (MAX_PATH, szOldPath);
    bResult = SetCurrentDirectory (pszPath);

    SetCurrentDirectory (szOldPath);

    return bResult;
}