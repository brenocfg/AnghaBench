#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ right; scalar_t__ bottom; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_11__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_12__ {int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_14__ {int pages_shown; scalar_t__ page; void* hdc2; TYPE_2__ bmSize; void* hdc; int /*<<< orphan*/  textlength; TYPE_3__ rcPage; } ;
struct TYPE_10__ {int /*<<< orphan*/  cpMax; scalar_t__ cpMin; } ;
struct TYPE_13__ {int /*<<< orphan*/  hdcTarget; TYPE_3__ rcPage; void* hdc; TYPE_1__ chrg; TYPE_3__ rc; } ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  TYPE_4__ FORMATRANGE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_EDITOR ; 
 int /*<<< orphan*/  IDC_PREVIEW ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_preview (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  make_dc () ; 
 TYPE_6__ margins ; 
 TYPE_5__ preview ; 
 int /*<<< orphan*/  update_preview_buttons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_preview_statusbar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_preview(HWND hMainWnd)
{
    RECT paper;
    HWND hEditorWnd = GetDlgItem(hMainWnd, IDC_EDITOR);
    HWND hwndPreview = GetDlgItem(hMainWnd, IDC_PREVIEW);
    HBITMAP hBitmapCapture;
    FORMATRANGE fr;
    HDC hdc = GetDC(hwndPreview);

    fr.hdcTarget = make_dc();
    fr.rc = fr.rcPage = preview.rcPage;
    fr.rc.left += margins.left;
    fr.rc.top += margins.top;
    fr.rc.bottom -= margins.bottom;
    fr.rc.right -= margins.right;

    fr.chrg.cpMin = 0;
    fr.chrg.cpMax = preview.textlength;

    SetRect(&paper, 0, 0, preview.bmSize.cx, preview.bmSize.cy);

    if (!preview.hdc) {
        preview.hdc = CreateCompatibleDC(hdc);
        hBitmapCapture = CreateCompatibleBitmap(hdc, preview.bmSize.cx, preview.bmSize.cy);
        SelectObject(preview.hdc, hBitmapCapture);
    }

    fr.hdc = preview.hdc;
    draw_preview(hEditorWnd, &fr, &paper, preview.page);

    if(preview.pages_shown > 1)
    {
        if (!preview.hdc2)
        {
            preview.hdc2 = CreateCompatibleDC(hdc);
            hBitmapCapture = CreateCompatibleBitmap(hdc,
                                                    preview.bmSize.cx,
                                                    preview.bmSize.cy);
            SelectObject(preview.hdc2, hBitmapCapture);
        }

        fr.hdc = preview.hdc2;
        draw_preview(hEditorWnd, &fr, &fr.rcPage, preview.page + 1);
    }
    DeleteDC(fr.hdcTarget);
    ReleaseDC(hwndPreview, hdc);

    InvalidateRect(hwndPreview, NULL, FALSE);
    update_preview_buttons(hMainWnd);
    update_preview_statusbar(hMainWnd);
}