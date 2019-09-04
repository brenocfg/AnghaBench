#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int MaximumLength; int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_6__ {TYPE_1__ Str; } ;
typedef  TYPE_2__* PSDB_TMP_STR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetLongPathNameW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHIM_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SdbpResizeTempStr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL SdbpGetLongPathName(PCWSTR wszPath, PSDB_TMP_STR Result)
{
    DWORD max = Result->Str.MaximumLength / 2;
    DWORD ret = GetLongPathNameW(wszPath, Result->Str.Buffer, max);
    if (ret)
    {
        if (ret >= max)
        {
            SdbpResizeTempStr(Result, ret);
            max = Result->Str.MaximumLength / 2;
            ret = GetLongPathNameW(wszPath, Result->Str.Buffer, max);
        }
        if (ret && ret < max)
        {
            Result->Str.Length = ret * 2;
            return TRUE;
        }
    }
    SHIM_ERR("Failed to convert short path to long path error 0x%lx\n", GetLastError());
    return FALSE;
}