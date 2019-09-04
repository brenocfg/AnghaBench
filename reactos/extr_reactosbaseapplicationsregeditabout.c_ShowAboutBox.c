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

/* Variables and functions */
 int /*<<< orphan*/  COUNT_OF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDI_REGEDIT ; 
 int /*<<< orphan*/  IDS_APP_TITLE ; 
 int /*<<< orphan*/  LoadIconW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShellAboutW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 

void ShowAboutBox(HWND hWnd)
{
    WCHAR AppStr[255];
    LoadStringW(hInst, IDS_APP_TITLE, AppStr, COUNT_OF(AppStr));
    ShellAboutW(hWnd, AppStr, L"", LoadIconW(hInst, MAKEINTRESOURCEW(IDI_REGEDIT)));
}