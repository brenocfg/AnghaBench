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
typedef  char WCHAR ;
struct TYPE_2__ {int pages_shown; scalar_t__ page; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_STATUSBAR ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int MAX_STRING_LEN ; 
 int /*<<< orphan*/  STRING_PREVIEW_PAGE ; 
 int /*<<< orphan*/  STRING_PREVIEW_PAGES ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_last_preview_page (scalar_t__) ; 
 TYPE_1__ preview ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,scalar_t__,...) ; 

__attribute__((used)) static void update_preview_statusbar(HWND hMainWnd)
{
    HWND hStatusbar = GetDlgItem(hMainWnd, IDC_STATUSBAR);
    HINSTANCE hInst = GetModuleHandleW(0);
    WCHAR *p;
    WCHAR wstr[MAX_STRING_LEN];

    p = wstr;
    if (preview.pages_shown < 2 || is_last_preview_page(preview.page))
    {
        static const WCHAR fmt[] = {' ','%','d','\0'};
        p += LoadStringW(hInst, STRING_PREVIEW_PAGE, wstr, MAX_STRING_LEN);
        wsprintfW(p, fmt, preview.page);
    } else {
        static const WCHAR fmt[] = {' ','%','d','-','%','d','\0'};
        p += LoadStringW(hInst, STRING_PREVIEW_PAGES, wstr, MAX_STRING_LEN);
        wsprintfW(p, fmt, preview.page, preview.page + 1);
    }
    SetWindowTextW(hStatusbar, wstr);
}