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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
typedef  scalar_t__* PWSTR ;
typedef  scalar_t__* PCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX_SAMPLES_STR_SIZE ; 
 int /*<<< orphan*/  wcscat (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__*,char*) ; 
 size_t wcslen (scalar_t__*) ; 

PWSTR
ReplaceSubStr(PCWSTR szSourceStr,
              PCWSTR szStrToReplace,
              PCWSTR szTempl)
{
    PWSTR szDestStr;
    UINT nCharCnt;
    UINT nSubStrCnt;
    UINT nDestStrCnt;
    UINT nFirstCharCnt;

    szDestStr = (PWSTR)HeapAlloc(GetProcessHeap(), 0, MAX_SAMPLES_STR_SIZE * sizeof(WCHAR));
    if (szDestStr == NULL)
        return NULL;

    nDestStrCnt = 0;
    nFirstCharCnt = 0;

    wcscpy(szDestStr, L"");

    while (nFirstCharCnt < wcslen(szSourceStr))
    {
        if (szSourceStr[nFirstCharCnt] == szTempl[0])
        {
            nSubStrCnt = 0;
            for (nCharCnt = nFirstCharCnt; nCharCnt < nFirstCharCnt + wcslen(szTempl); nCharCnt++)
            {
                if (szSourceStr[nCharCnt] == szTempl[nSubStrCnt])
                {
                    nSubStrCnt++;
                }
                else
                {
                    break;
                }

                if (wcslen(szTempl) == nSubStrCnt)
                {
                    wcscat(szDestStr, szStrToReplace);
                    nDestStrCnt = wcslen(szDestStr);
                    nFirstCharCnt += wcslen(szTempl) - 1;
                    break;
                }
            }
        }
        else
        {
            szDestStr[nDestStrCnt++] = szSourceStr[nFirstCharCnt];
            szDestStr[nDestStrCnt] = L'\0';
        }

        nFirstCharCnt++;
    }

    return szDestStr;
}