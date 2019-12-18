#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  openfilename ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  hInstance; } ;
struct TYPE_5__ {int lStructSize; char* lpstrDefExt; int /*<<< orphan*/ * lpTemplateName; int /*<<< orphan*/ * lpfnHook; scalar_t__ lCustData; scalar_t__ nFileExtension; scalar_t__ nFileOffset; int /*<<< orphan*/ * lpstrTitle; scalar_t__ nMaxFileTitle; int /*<<< orphan*/ * lpstrFileTitle; scalar_t__ nFilterIndex; scalar_t__ nMaxCustFilter; int /*<<< orphan*/ * lpstrCustomFilter; scalar_t__ Flags; int /*<<< orphan*/ * lpstrInitialDir; int /*<<< orphan*/  nMaxFile; int /*<<< orphan*/  lpstrFile; int /*<<< orphan*/  lpstrFilter; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_1__ OPENFILENAMEW ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetOpenFileNameW (TYPE_1__*) ; 
 TYPE_3__ Globals ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static
BOOL
DIALOG_Browse(HWND hWnd, LPCWSTR lpszzFilter, LPWSTR lpstrFile, INT nMaxFile)
{
    OPENFILENAMEW openfilename;
    WCHAR szDir[MAX_PATH];

    ZeroMemory(&openfilename, sizeof(openfilename));

    GetCurrentDirectoryW(ARRAYSIZE(szDir), szDir);

    openfilename.lStructSize       = sizeof(openfilename);
    openfilename.hwndOwner         = hWnd;
    openfilename.hInstance         = Globals.hInstance;
    openfilename.lpstrFilter       = lpszzFilter;
    openfilename.lpstrFile         = lpstrFile;
    openfilename.nMaxFile          = nMaxFile;
    openfilename.lpstrInitialDir   = szDir;
    openfilename.Flags             = 0;
    openfilename.lpstrDefExt       = L"exe";
    openfilename.lpstrCustomFilter = NULL;
    openfilename.nMaxCustFilter    = 0;
    openfilename.nFilterIndex      = 0;
    openfilename.lpstrFileTitle    = NULL;
    openfilename.nMaxFileTitle     = 0;
    openfilename.lpstrTitle        = NULL;
    openfilename.nFileOffset       = 0;
    openfilename.nFileExtension    = 0;
    openfilename.lCustData         = 0;
    openfilename.lpfnHook          = NULL;
    openfilename.lpTemplateName    = NULL;

    return GetOpenFileNameW(&openfilename);
}