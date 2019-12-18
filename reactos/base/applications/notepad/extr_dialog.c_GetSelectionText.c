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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EM_GETSEL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetWindowText (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ GetWindowTextLength (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
#define  STRSAFE_E_INSUFFICIENT_BUFFER 129 
#define  S_OK 128 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StringCchCopyN (scalar_t__,int,scalar_t__,scalar_t__) ; 

int GetSelectionText(HWND hWnd, LPTSTR lpString, int nMaxCount)
{
    DWORD dwStart = 0;
    DWORD dwEnd = 0;
    DWORD dwSize;
    HRESULT hResult;
    LPTSTR lpTemp;

    if (!lpString)
    {
        return 0;
    }

    SendMessage(hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);

    if (dwStart == dwEnd)
    {
        return 0;
    }

    dwSize = GetWindowTextLength(hWnd) + 1;
    lpTemp = HeapAlloc(GetProcessHeap(), 0, dwSize * sizeof(TCHAR));
    if (!lpTemp)
    {
        return 0;
    }

    dwSize = GetWindowText(hWnd, lpTemp, dwSize);

    if (!dwSize)
    {
        HeapFree(GetProcessHeap(), 0, lpTemp);
        return 0;
    }

    hResult = StringCchCopyN(lpString, nMaxCount, lpTemp + dwStart, dwEnd - dwStart);
    HeapFree(GetProcessHeap(), 0, lpTemp);

    switch (hResult)
    {
        case S_OK:
        {
            return dwEnd - dwStart;
        }

        case STRSAFE_E_INSUFFICIENT_BUFFER:
        {
            return nMaxCount - 1;
        }

        default:
        {
            return 0;
        }
    }
}