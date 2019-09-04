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
struct TYPE_2__ {int page; scalar_t__ zoomlevel; scalar_t__ zoomratio; int /*<<< orphan*/  wszFileName; scalar_t__ hdc2; scalar_t__ hdc; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_PREVIEW ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_CHILD ; 
 int WS_HSCROLL ; 
 int WS_VISIBLE ; 
 int WS_VSCROLL ; 
 TYPE_1__ preview ; 
 int /*<<< orphan*/  preview_bar_show (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wszPreviewWndClass ; 

void init_preview(HWND hMainWnd, LPWSTR wszFileName)
{
    HINSTANCE hInstance = GetModuleHandleW(0);
    preview.page = 1;
    preview.hdc = 0;
    preview.hdc2 = 0;
    preview.wszFileName = wszFileName;
    preview.zoomratio = 0;
    preview.zoomlevel = 0;
    preview_bar_show(hMainWnd, TRUE);

    CreateWindowExW(0, wszPreviewWndClass, NULL,
            WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL,
            0, 0, 200, 10, hMainWnd, (HMENU)IDC_PREVIEW, hInstance, NULL);
}