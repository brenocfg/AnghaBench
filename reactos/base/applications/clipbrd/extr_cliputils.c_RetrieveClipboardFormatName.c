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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CF_OWNERDISPLAY ; 
 int /*<<< orphan*/  GetClipboardFormatNameA (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetClipboardFormatNameW (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetPredefinedClipboardFormatName (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  LoadStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STRING_CF_UNKNOWN ; 
 scalar_t__ SendClipboardOwnerMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_ASKCBFORMATNAME ; 
 int /*<<< orphan*/  ZeroMemory (scalar_t__,int) ; 

void
RetrieveClipboardFormatName(HINSTANCE hInstance,
                            UINT uFormat,
                            BOOL Unicode,
                            PVOID lpszFormat,
                            UINT cch)
{
    ZeroMemory(lpszFormat, cch * (Unicode ? sizeof(WCHAR) : sizeof(CHAR)));

    /* Check for predefined clipboard format */
    if (GetPredefinedClipboardFormatName(hInstance, uFormat, Unicode, lpszFormat, cch) != 0)
        return;

    /* Check for owner-display format */
    if (uFormat == CF_OWNERDISPLAY)
    {
        if (SendClipboardOwnerMessage(Unicode, WM_ASKCBFORMATNAME,
                                      (WPARAM)cch, (LPARAM)lpszFormat) != 0)
        {
            if (Unicode)
                LoadStringW(hInstance, STRING_CF_UNKNOWN, (LPWSTR)lpszFormat, cch);
            else
                LoadStringA(hInstance, STRING_CF_UNKNOWN, (LPSTR)lpszFormat, cch);
        }
        return;
    }

    /* Fallback to registered clipboard format */
    if (Unicode)
    {
        if (!GetClipboardFormatNameW(uFormat, (LPWSTR)lpszFormat, cch))
            LoadStringW(hInstance, STRING_CF_UNKNOWN, (LPWSTR)lpszFormat, cch);
    }
    else
    {
        if (!GetClipboardFormatNameA(uFormat, (LPSTR)lpszFormat, cch))
            LoadStringA(hInstance, STRING_CF_UNKNOWN, (LPSTR)lpszFormat, cch);
    }
}