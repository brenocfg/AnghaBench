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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int pages_shown; scalar_t__ zoomlevel; int saved_pages_shown; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PREVIEW ; 
 int /*<<< orphan*/  IDC_REBAR ; 
 int /*<<< orphan*/  ID_PREVIEW_NUMPAGES ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_STRING_LEN ; 
 int /*<<< orphan*/  STRING_PREVIEW_ONEPAGE ; 
 int /*<<< orphan*/  STRING_PREVIEW_TWOPAGES ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ preview ; 
 int /*<<< orphan*/  update_preview (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_preview_sizes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toggle_num_pages(HWND hMainWnd)
{
    HWND hReBar = GetDlgItem(hMainWnd, IDC_REBAR);
    WCHAR name[MAX_STRING_LEN];
    HINSTANCE hInst = GetModuleHandleW(0);
    int nPreviewPages;

    preview.pages_shown = preview.pages_shown > 1 ? 1 : 2;

    nPreviewPages = preview.zoomlevel > 0 ? preview.saved_pages_shown :
                                            preview.pages_shown;

    LoadStringW(hInst, nPreviewPages > 1 ? STRING_PREVIEW_ONEPAGE :
                                           STRING_PREVIEW_TWOPAGES,
                name, MAX_STRING_LEN);

    SetWindowTextW(GetDlgItem(hReBar, ID_PREVIEW_NUMPAGES), name);
    update_preview_sizes(GetDlgItem(hMainWnd, IDC_PREVIEW), TRUE);
    update_preview(hMainWnd);
}