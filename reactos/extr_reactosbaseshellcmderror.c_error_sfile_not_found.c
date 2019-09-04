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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMD_ModuleHandle ; 
 int /*<<< orphan*/  ConErrPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RC_STRING_MAX_SIZE ; 
 int /*<<< orphan*/  STRING_ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  _T (char*) ; 
 int nErrorLevel ; 

VOID error_sfile_not_found (LPTSTR f)
{
    TCHAR szMsg[RC_STRING_MAX_SIZE];

    LoadString(CMD_ModuleHandle, STRING_ERROR_FILE_NOT_FOUND, szMsg, ARRAYSIZE(szMsg));
    ConErrPrintf(_T("%s - %s\n"), szMsg, f);
    nErrorLevel = 1;
}