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
typedef  int /*<<< orphan*/  szTempMessage ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  MCIERROR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDS_DEFAULTMCIERRMSG ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_MCISTR ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StringCbPrintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  hInstance ; 
 scalar_t__ mciGetErrorString (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szAppTitle ; 

__attribute__((used)) static VOID
ShowMCIError(HWND hwnd, MCIERROR mciError)
{
    TCHAR szErrorMessage[MAX_MCISTR];
    TCHAR szTempMessage[MAX_MCISTR + 44];

    if (mciGetErrorString(mciError, szErrorMessage, ARRAYSIZE(szErrorMessage)) == FALSE)
    {
        LoadString(hInstance, IDS_DEFAULTMCIERRMSG, szErrorMessage, ARRAYSIZE(szErrorMessage));
    }

    StringCbPrintf(szTempMessage, sizeof(szTempMessage), _T("MMSYS%lu: %s"), mciError, szErrorMessage);
    MessageBox(hwnd, szTempMessage, szAppTitle, MB_OK | MB_ICONEXCLAMATION);
}