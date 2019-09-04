#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bottom; scalar_t__ right; } ;
struct TYPE_4__ {scalar_t__ zoomlevel; int /*<<< orphan*/ * hdc2; int /*<<< orphan*/ * hdc; int /*<<< orphan*/  saved_pages_shown; int /*<<< orphan*/  pages_shown; scalar_t__ pageCapacity; int /*<<< orphan*/ * pageEnds; scalar_t__ page; TYPE_1__ window; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_PREVIEW ; 
 int /*<<< orphan*/  OBJ_BITMAP ; 
 TYPE_2__ preview ; 
 int /*<<< orphan*/  preview_bar_show (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void close_preview(HWND hMainWnd)
{
    HWND hwndPreview = GetDlgItem(hMainWnd, IDC_PREVIEW);
    preview.window.right = 0;
    preview.window.bottom = 0;
    preview.page = 0;
    HeapFree(GetProcessHeap(), 0, preview.pageEnds);
    preview.pageEnds = NULL;
    preview.pageCapacity = 0;
    if (preview.zoomlevel > 0)
        preview.pages_shown = preview.saved_pages_shown;
    if(preview.hdc) {
        HBITMAP oldbm = GetCurrentObject(preview.hdc, OBJ_BITMAP);
        DeleteDC(preview.hdc);
        DeleteObject(oldbm);
        preview.hdc = NULL;
    }
    if(preview.hdc2) {
        HBITMAP oldbm = GetCurrentObject(preview.hdc2, OBJ_BITMAP);
        DeleteDC(preview.hdc2);
        DeleteObject(oldbm);
        preview.hdc2 = NULL;
    }

    preview_bar_show(hMainWnd, FALSE);
    DestroyWindow(hwndPreview);
}