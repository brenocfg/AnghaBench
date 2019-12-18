#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct font_metrics {int /*<<< orphan*/  facename; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  lfFaceName; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ LOGFONTW ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFontIndirectW (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnumFontFamiliesW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FontFamilyNotFound ; 
 int /*<<< orphan*/  NotTrueTypeFont ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_font_metrics (int /*<<< orphan*/ ,struct font_metrics*) ; 
 int /*<<< orphan*/  is_font_installed_proc ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GpStatus find_installed_font(const WCHAR *name, struct font_metrics *fm)
{
    LOGFONTW lf;
    HDC hdc = CreateCompatibleDC(0);
    GpStatus ret = FontFamilyNotFound;

    if(!EnumFontFamiliesW(hdc, name, is_font_installed_proc, (LPARAM)&lf))
    {
        HFONT hfont, old_font;

        strcpyW(fm->facename, lf.lfFaceName);

        hfont = CreateFontIndirectW(&lf);
        old_font = SelectObject(hdc, hfont);
        ret = get_font_metrics(hdc, fm) ? Ok : NotTrueTypeFont;
        SelectObject(hdc, old_font);
        DeleteObject(hfont);
    }

    DeleteDC(hdc);
    return ret;
}