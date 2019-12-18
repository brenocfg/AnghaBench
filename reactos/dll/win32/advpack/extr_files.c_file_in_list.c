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
typedef  scalar_t__* LPCSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcmpiA (scalar_t__*,scalar_t__*) ; 
 scalar_t__ lstrlenA (scalar_t__*) ; 

__attribute__((used)) static BOOL file_in_list(LPCSTR szFile, LPCSTR szFileList)
{
    DWORD dwLen = lstrlenA(szFile);
    DWORD dwTestLen;

    while (*szFileList)
    {
        dwTestLen = lstrlenA(szFileList);

        if (dwTestLen == dwLen)
        {
            if (!lstrcmpiA(szFile, szFileList))
                return TRUE;
        }

        szFileList += dwTestLen + 1;
    }

    return FALSE;
}