#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int WCHAR ;
typedef  int UINT ;
struct TYPE_4__ {int* pszText; int /*<<< orphan*/  mask; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hParent; TYPE_1__ item; int /*<<< orphan*/  hInsertAfter; } ;
typedef  TYPE_2__ TVINSERTSTRUCT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HTREEITEM ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SYSTEM_TREE ; 
 int /*<<< orphan*/  StringCbCatW (int*,int,char*) ; 
 int /*<<< orphan*/  StringCbCopyW (int*,int,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TVIF_TEXT ; 
 int /*<<< orphan*/  TVI_LAST ; 
 int /*<<< orphan*/ * TreeView_InsertItem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * _wfopen (int*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fgetws (int*,int,int /*<<< orphan*/ *) ; 
 int wcslen (int*) ; 

__attribute__((used)) static BOOL
LoadSystemIni(WCHAR * szPath, HWND hDlg)
{
    WCHAR szBuffer[BUFFER_SIZE];
    HWND hDlgCtrl;
    HTREEITEM parent = NULL;
    FILE* file;
    UINT length;
    TVINSERTSTRUCT insert;
    HRESULT hr;

    hr = StringCbCopyW(szBuffer, sizeof(szBuffer), szPath);
    if (FAILED(hr))
        return FALSE;

    hr = StringCbCatW(szBuffer, sizeof(szBuffer), L"\\system.ini");
    if (FAILED(hr))
        return FALSE;

    file = _wfopen(szBuffer, L"rt");
    if (!file)
       return FALSE;

    hDlgCtrl = GetDlgItem(hDlg, IDC_SYSTEM_TREE);

    while(!feof(file))
    {
        if (fgetws(szBuffer, BUFFER_SIZE, file))
        {
            length = wcslen(szBuffer);
            if (length > 1)
            {
                szBuffer[length] = L'\0';
                szBuffer[length - 1] = L'\0';
                insert.hInsertAfter = TVI_LAST;
                insert.item.mask = TVIF_TEXT;
                insert.item.pszText = szBuffer;

                if (szBuffer[0] == L';' || szBuffer[0] == L'[')
                {
                    /* Parent */
                    insert.hParent = NULL;
                    parent = TreeView_InsertItem(hDlgCtrl, &insert);
                }
                else
                {
                    /* Child */
                    insert.hParent = parent;
                    TreeView_InsertItem(hDlgCtrl, &insert);
                }
            }
        }
    }

    fclose(file);

    return TRUE;
}