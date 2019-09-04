#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dwPlatformId; int /*<<< orphan*/  wServicePackMinor; int /*<<< orphan*/  wServicePackMajor; int /*<<< orphan*/  szCSDVersionW; int /*<<< orphan*/  szCSDVersionA; int /*<<< orphan*/  dwBuildNumber; int /*<<< orphan*/  dwMinorVersion; int /*<<< orphan*/  dwMajorVersion; } ;
typedef  TYPE_1__ VersionLieInfo ;
struct TYPE_8__ {int dwOSVersionInfoSize; scalar_t__ dwPlatformId; int /*<<< orphan*/  wServicePackMinor; int /*<<< orphan*/  wServicePackMajor; int /*<<< orphan*/  szCSDVersion; int /*<<< orphan*/  dwBuildNumber; int /*<<< orphan*/  dwMinorVersion; int /*<<< orphan*/  dwMajorVersion; } ;
struct TYPE_7__ {int dwOSVersionInfoSize; int /*<<< orphan*/  wServicePackMinor; int /*<<< orphan*/  wServicePackMajor; int /*<<< orphan*/  szCSDVersion; } ;
typedef  int /*<<< orphan*/  OSVERSIONINFOW ;
typedef  int /*<<< orphan*/  OSVERSIONINFOEXW ;
typedef  int /*<<< orphan*/  OSVERSIONINFOEXA ;
typedef  int /*<<< orphan*/  OSVERSIONINFOA ;
typedef  TYPE_2__* LPOSVERSIONINFOEXW ;
typedef  TYPE_3__* LPOSVERSIONINFOEXA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  StringCbCopyA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCbCopyW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VER_PLATFORM_WIN32_WINDOWS ; 

BOOL FakeVersion(LPOSVERSIONINFOEXA pResult, VersionLieInfo* pFake)
{
    if (pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA) || pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA) ||
        pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXW) || pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOW))
    {
        pResult->dwMajorVersion = pFake->dwMajorVersion;
        pResult->dwMinorVersion = pFake->dwMinorVersion;
        pResult->dwBuildNumber = pFake->dwBuildNumber;
        pResult->dwPlatformId = pFake->dwPlatformId;
        if (pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA) || pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA))
        {
            if (FAILED(StringCbCopyA(pResult->szCSDVersion, sizeof(pResult->szCSDVersion), pFake->szCSDVersionA)))
                return FALSE;
            if (pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA) && pFake->dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
            {
                pResult->wServicePackMajor = pFake->wServicePackMajor;
                pResult->wServicePackMinor = pFake->wServicePackMinor;
            }
        }
        else
        {
            LPOSVERSIONINFOEXW pResultW = (LPOSVERSIONINFOEXW)pResult;
            if (FAILED(StringCbCopyW(pResultW->szCSDVersion, sizeof(pResultW->szCSDVersion), pFake->szCSDVersionW)))
                return FALSE;
            if (pResultW->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXW) && pFake->dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
            {
                pResultW->wServicePackMajor = pFake->wServicePackMajor;
                pResultW->wServicePackMinor = pFake->wServicePackMinor;
            }
        }
        return TRUE;
    }
    return FALSE;
}