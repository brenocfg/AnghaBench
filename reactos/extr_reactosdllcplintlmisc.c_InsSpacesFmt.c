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
typedef  int WCHAR ;
typedef  size_t UINT ;
typedef  int* PWSTR ;
typedef  int* PCWSTR ;
typedef  size_t INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int* InsSpacePos (int*,size_t) ; 
 scalar_t__ TRUE ; 
 scalar_t__ _wtoi (int*) ; 
 int /*<<< orphan*/  wcscpy (int*,int*) ; 
 size_t wcslen (int*) ; 

PWSTR
InsSpacesFmt(PCWSTR szSourceStr, PCWSTR szFmtStr)
{
    PWSTR pszDestStr;
    PWSTR pszTempStr;
    WCHAR szFmtVal[255];
    UINT nFmtCount = 0;
    INT nValCount = 0;
    INT nLastVal = 0;
    INT nSpaceOffset = 0;
    BOOL wasNul=FALSE;

    pszDestStr = (PWSTR)HeapAlloc(GetProcessHeap(), 0, 255 * sizeof(WCHAR));
    if (pszDestStr == NULL)
        return NULL;

    wcscpy(pszDestStr, szSourceStr);

    /* If format is clean return source string */
    if (!*szFmtStr)
        return pszDestStr;

    /* Search for all format values */
    for (nFmtCount = 0; nFmtCount <= wcslen(szFmtStr); nFmtCount++)
    {
        if (szFmtStr[nFmtCount] == L';' || szFmtStr[nFmtCount] == L'\0')
        {
            if (_wtoi(szFmtVal) == 0 && !wasNul)
            {
                wasNul=TRUE;
                break;
            }

            /* If was 0, repeat spaces */
            if (wasNul)
            {
                nSpaceOffset += nLastVal;
            }
            else
            {
                nSpaceOffset += _wtoi(szFmtVal);
            }

            szFmtVal[nValCount] = L'\0';
            nValCount=0;

            /* Insert space to finded position plus all pos before */
            pszTempStr = InsSpacePos(pszDestStr, nSpaceOffset);
            wcscpy(pszDestStr,pszTempStr);
            HeapFree(GetProcessHeap(), 0, pszTempStr);

            /* Num of spaces total increment */
            if (!wasNul)
            {
                nSpaceOffset++;
                nLastVal = _wtoi(szFmtVal);
            }
        }
        else
        {
            szFmtVal[nValCount++] = szFmtStr[nFmtCount];
        }
    }

    /* Create spaces for rest part of string */
    if (wasNul && nLastVal != 0)
    {
        for (nFmtCount = nSpaceOffset + nLastVal; nFmtCount < wcslen(pszDestStr); nFmtCount += nLastVal + 1)
        {
            pszTempStr = InsSpacePos(pszDestStr, nFmtCount);
            wcscpy(pszDestStr, pszTempStr);
            HeapFree(GetProcessHeap(), 0, pszTempStr);
        }
    }

    return pszDestStr;
}