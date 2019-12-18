#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {char* File; } ;
typedef  TYPE_2__ MSISIGNATURE ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ACTION_FileMatchesSig (TYPE_2__*,TYPE_1__*,char*,scalar_t__*) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathAddBackslashW (char*) ; 
 int /*<<< orphan*/  PathAppendW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 size_t lstrlenW (char*) ; 
 int max (size_t,int /*<<< orphan*/ ) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 scalar_t__ strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlenW (char const*) ; 
 int /*<<< orphan*/  szDot ; 
 int /*<<< orphan*/  szDotDot ; 

__attribute__((used)) static UINT ACTION_RecurseSearchDirectory(MSIPACKAGE *package, LPWSTR *appValue,
 MSISIGNATURE *sig, LPCWSTR dir, int depth)
{
    HANDLE hFind;
    WIN32_FIND_DATAW findData;
    UINT rc = ERROR_SUCCESS;
    size_t dirLen = lstrlenW(dir), fileLen = lstrlenW(sig->File);
    WCHAR subpath[MAX_PATH];
    WCHAR *buf;
    DWORD len;

    static const WCHAR starDotStarW[] = { '*','.','*',0 };

    TRACE("Searching directory %s for file %s, depth %d\n", debugstr_w(dir),
          debugstr_w(sig->File), depth);

    if (depth < 0)
        return ERROR_SUCCESS;

    *appValue = NULL;
    /* We need the buffer in both paths below, so go ahead and allocate it
     * here.  Add two because we might need to add a backslash if the dir name
     * isn't backslash-terminated.
     */
    len = dirLen + max(fileLen, strlenW(starDotStarW)) + 2;
    buf = msi_alloc(len * sizeof(WCHAR));
    if (!buf)
        return ERROR_OUTOFMEMORY;

    lstrcpyW(buf, dir);
    PathAddBackslashW(buf);
    lstrcatW(buf, sig->File);

    hFind = FindFirstFileW(buf, &findData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            BOOL matches;

            rc = ACTION_FileMatchesSig(sig, &findData, buf, &matches);
            if (rc == ERROR_SUCCESS && matches)
            {
                TRACE("found file, returning %s\n", debugstr_w(buf));
                *appValue = buf;
            }
        }
        FindClose(hFind);
    }

    if (rc == ERROR_SUCCESS && !*appValue)
    {
        lstrcpyW(buf, dir);
        PathAddBackslashW(buf);
        lstrcatW(buf, starDotStarW);

        hFind = FindFirstFileW(buf, &findData);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
                strcmpW( findData.cFileName, szDot ) &&
                strcmpW( findData.cFileName, szDotDot ))
            {
                lstrcpyW(subpath, dir);
                PathAppendW(subpath, findData.cFileName);
                rc = ACTION_RecurseSearchDirectory(package, appValue, sig,
                                                   subpath, depth - 1);
            }

            while (rc == ERROR_SUCCESS && !*appValue &&
                   FindNextFileW(hFind, &findData) != 0)
            {
                if (!strcmpW( findData.cFileName, szDot ) ||
                    !strcmpW( findData.cFileName, szDotDot ))
                    continue;

                lstrcpyW(subpath, dir);
                PathAppendW(subpath, findData.cFileName);
                if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    rc = ACTION_RecurseSearchDirectory(package, appValue,
                                                       sig, subpath, depth - 1);
            }

            FindClose(hFind);
        }
    }

    if (*appValue != buf)
        msi_free(buf);

    return rc;
}