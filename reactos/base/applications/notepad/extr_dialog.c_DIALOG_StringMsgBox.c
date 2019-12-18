#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hInstance; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_STRING_LEN ; 
 int MB_ICONEXCLAMATION ; 
 int MB_ICONMASK ; 
 int MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int STRING_ERROR ; 
 int STRING_NOTEPAD ; 
 int /*<<< orphan*/  _sntprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int DIALOG_StringMsgBox(HWND hParent, int formatId, LPCTSTR szString, DWORD dwFlags)
{
    TCHAR szMessage[MAX_STRING_LEN];
    TCHAR szResource[MAX_STRING_LEN];

    /* Load and format szMessage */
    LoadString(Globals.hInstance, formatId, szResource, ARRAY_SIZE(szResource));
    _sntprintf(szMessage, ARRAY_SIZE(szMessage), szResource, szString);

    /* Load szCaption */
    if ((dwFlags & MB_ICONMASK) == MB_ICONEXCLAMATION)
        LoadString(Globals.hInstance, STRING_ERROR, szResource, ARRAY_SIZE(szResource));
    else
        LoadString(Globals.hInstance, STRING_NOTEPAD, szResource, ARRAY_SIZE(szResource));

    /* Display Modal Dialog */
    // if (hParent == NULL)
        // hParent = Globals.hMainWnd;
    return MessageBox(hParent, szMessage, szResource, dwFlags);
}