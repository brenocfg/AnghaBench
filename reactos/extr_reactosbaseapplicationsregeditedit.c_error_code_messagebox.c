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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT_OF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ErrorMessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_ERROR ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void error_code_messagebox(HWND hwnd, DWORD error_code)
{
    WCHAR title[256];
    if (!LoadStringW(hInst, IDS_ERROR, title, COUNT_OF(title)))
        wcscpy(title, L"Error");
    ErrorMessageBox(hwnd, title, error_code);
}