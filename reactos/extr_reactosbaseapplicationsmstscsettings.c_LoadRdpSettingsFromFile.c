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
typedef  int /*<<< orphan*/  PRDPSETTINGS ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_PERSONAL ; 
 int /*<<< orphan*/  CloseRdpFile (scalar_t__) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ OpenRdpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParseSettings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadRdpFile (scalar_t__) ; 
 scalar_t__ SHGetFolderLocation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ SHGetPathFromIDListW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,char*) ; 

BOOL
LoadRdpSettingsFromFile(PRDPSETTINGS pRdpSettings,
                        LPWSTR lpFile)
{
    WCHAR pszPath[MAX_PATH];
    HANDLE hFile;
    BOOL bRet = FALSE;

    /* use default file */
    if (lpFile == NULL)
    {
        HRESULT hr;
        LPITEMIDLIST lpidl= NULL;

        hr = SHGetFolderLocation(NULL,
                                 CSIDL_PERSONAL,
                                 NULL,
                                 0,
                                 &lpidl);
        if (hr == S_OK)
        {
            if (SHGetPathFromIDListW(lpidl, pszPath))
            {
                wcscat(pszPath, L"\\Default.rdp");
                lpFile = pszPath;
                CoTaskMemFree(lpidl);
            }
        }
    }

    if (lpFile)
    {
        LPWSTR lpBuffer = NULL;

        hFile = OpenRdpFile(lpFile, FALSE);
        if (hFile)
        {
            lpBuffer = ReadRdpFile(hFile);
            if (lpBuffer)
            {
                ParseSettings(pRdpSettings, lpBuffer);

                HeapFree(GetProcessHeap(),
                         0,
                         lpBuffer);
                
                bRet = TRUE;
            }

            CloseRdpFile(hFile);
        }
    }

    return bRet;
}