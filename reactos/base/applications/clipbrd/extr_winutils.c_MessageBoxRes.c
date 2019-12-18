#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mb ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  dwLanguageId; int /*<<< orphan*/  dwStyle; void* lpszCaption; void* lpszText; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_1__ MSGBOXPARAMSW ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 void* MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MessageBoxIndirectW (TYPE_1__*) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

int MessageBoxRes(HWND hWnd, HINSTANCE hInstance, UINT uText, UINT uCaption, UINT uType)
{
    MSGBOXPARAMSW mb;

    ZeroMemory(&mb, sizeof(mb));
    mb.cbSize = sizeof(mb);
    mb.hwndOwner = hWnd;
    mb.hInstance = hInstance;
    mb.lpszText = MAKEINTRESOURCEW(uText);
    mb.lpszCaption = MAKEINTRESOURCEW(uCaption);
    mb.dwStyle = uType;
    mb.dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);

    return MessageBoxIndirectW(&mb);
}