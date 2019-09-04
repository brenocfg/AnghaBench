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
typedef  int /*<<< orphan*/  wchar_t ;
struct nk_color {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_1__ GdiFont ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,short,short,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _alloca (int) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 

__attribute__((used)) static void
nk_gdi_draw_text(HDC dc, short x, short y, unsigned short w, unsigned short h,
    const char *text, int len, GdiFont *font, struct nk_color cbg, struct nk_color cfg)
{
    int wsize;
    WCHAR* wstr;

    if(!text || !font || !len) return;

    wsize = MultiByteToWideChar(CP_UTF8, 0, text, len, NULL, 0);
    wstr = (WCHAR*)_alloca(wsize * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, text, len, wstr, wsize);

    SetBkColor(dc, convert_color(cbg));
    SetTextColor(dc, convert_color(cfg));

    SelectObject(dc, font->handle);
    ExtTextOutW(dc, x, y, ETO_OPAQUE, NULL, wstr, wsize, NULL);
}