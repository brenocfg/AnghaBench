#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int dwFileAttributes; int nFileSizeLow; } ;
typedef  TYPE_2__ WIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
struct TYPE_11__ {int Length; scalar_t__ Buffer; int /*<<< orphan*/  MaximumLength; } ;
struct TYPE_13__ {TYPE_1__ Str; } ;
typedef  TYPE_3__ SDB_TMP_STR ;
typedef  char* PWCHAR ;
typedef  TYPE_3__* PSDB_TMP_STR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (scalar_t__,TYPE_2__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_2__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SIGN_MEDIA_FMT ; 
 int /*<<< orphan*/  SdbpFreeTempStr (TYPE_3__*) ; 
 int /*<<< orphan*/  SdbpInitTempStr (TYPE_3__*) ; 
 int /*<<< orphan*/  SdbpResizeTempStr (TYPE_3__*,int) ; 
 scalar_t__ SdbpStrlen (scalar_t__) ; 
 int /*<<< orphan*/  StringCbCopyNW (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  StringCbPrintfW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 char* wcsrchr (scalar_t__,char) ; 

BOOL SdbpBuildSignMediaId(PSDB_TMP_STR LongPath)
{
    SDB_TMP_STR Scratch;
    PWCHAR Ptr;

    SdbpInitTempStr(&Scratch);
    SdbpResizeTempStr(&Scratch, LongPath->Str.Length / sizeof(WCHAR) + 30);
    StringCbCopyNW(Scratch.Str.Buffer, Scratch.Str.MaximumLength, LongPath->Str.Buffer, LongPath->Str.Length);
    Ptr = wcsrchr(LongPath->Str.Buffer, '\\');
    if (Ptr)
    {
        HANDLE FindHandle;
        WIN32_FIND_DATAW FindData;
        Ptr[1] = '*';
        Ptr[2] = '\0';
        FindHandle = FindFirstFileW(LongPath->Str.Buffer, &FindData);
        if (FindHandle != INVALID_HANDLE_VALUE)
        {
            DWORD SignMedia = 0;
            do
            {
                if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && FindData.nFileSizeLow)
                    SignMedia = SignMedia << 1 ^ FindData.nFileSizeLow;
            } while (FindNextFileW(FindHandle, &FindData));

            FindClose(FindHandle);
            SdbpResizeTempStr(LongPath, (LongPath->Str.Length >> 1) + 20);
            StringCbPrintfW(LongPath->Str.Buffer, LongPath->Str.MaximumLength, SIGN_MEDIA_FMT, SignMedia, Scratch.Str.Buffer + 3);
            LongPath->Str.Length = (USHORT)SdbpStrlen(LongPath->Str.Buffer) * sizeof(WCHAR);
            SdbpFreeTempStr(&Scratch);
            return TRUE;
        }
    }
    SdbpFreeTempStr(&Scratch);
    SdbpFreeTempStr(LongPath);
    return FALSE;
}