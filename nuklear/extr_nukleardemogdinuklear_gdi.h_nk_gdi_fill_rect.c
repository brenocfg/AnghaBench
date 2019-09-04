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
struct nk_color {int dummy; } ;
struct TYPE_3__ {short member_0; short member_1; short member_2; short member_3; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RoundRect (int /*<<< orphan*/ ,short,short,short,short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCBrushColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 

__attribute__((used)) static void
nk_gdi_fill_rect(HDC dc, short x, short y, unsigned short w,
    unsigned short h, unsigned short r, struct nk_color col)
{
    COLORREF color = convert_color(col);

    if (r == 0) {
        RECT rect = { x, y, x + w, y + h };
        SetBkColor(dc, color);
        ExtTextOutW(dc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
    } else {
        SetDCPenColor(dc, color);
        SetDCBrushColor(dc, color);
        RoundRect(dc, x, y, x + w, y + h, r, r);
    }
}