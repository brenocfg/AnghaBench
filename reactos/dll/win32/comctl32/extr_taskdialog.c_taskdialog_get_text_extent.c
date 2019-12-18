#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct taskdialog_template_desc {int /*<<< orphan*/  font; TYPE_1__* taskconfig; int /*<<< orphan*/  dialog_width; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT_PTR ;
struct TYPE_8__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_6__ {int /*<<< orphan*/  hInstance; } ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COMCTL32_hModule ; 
 int DIALOG_SPACING ; 
 int DT_CALCRECT ; 
 int DT_EXPANDTABS ; 
 int DT_LEFT ; 
 int DT_WORDBREAK ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_INTRESOURCE (int /*<<< orphan*/  const*) ; 
 unsigned int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  dialogunits_to_pixels (struct taskdialog_template_desc const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixels_to_dialogunits (struct taskdialog_template_desc const*,scalar_t__*,scalar_t__*) ; 
 unsigned int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void taskdialog_get_text_extent(const struct taskdialog_template_desc *desc, const WCHAR *text,
        BOOL user_resource, SIZE *sz)
{
    RECT rect = { 0, 0, desc->dialog_width - DIALOG_SPACING * 2, 0}; /* padding left and right of the control */
    const WCHAR *textW = NULL;
    static const WCHAR nulW;
    unsigned int length;
    HFONT oldfont;
    HDC hdc;

    if (IS_INTRESOURCE(text))
    {
        if (!(length = LoadStringW(user_resource ? desc->taskconfig->hInstance : COMCTL32_hModule,
                (UINT_PTR)text, (WCHAR *)&textW, 0)))
        {
            WARN("Failed to load text\n");
            textW = &nulW;
            length = 0;
        }
    }
    else
    {
        textW = text;
        length = strlenW(textW);
    }

    hdc = GetDC(0);
    oldfont = SelectObject(hdc, desc->font);

    dialogunits_to_pixels(desc, &rect.right, NULL);
    DrawTextW(hdc, textW, length, &rect, DT_LEFT | DT_EXPANDTABS | DT_CALCRECT | DT_WORDBREAK);
    pixels_to_dialogunits(desc, &rect.right, &rect.bottom);

    SelectObject(hdc, oldfont);
    ReleaseDC(0, hdc);

    sz->cx = rect.right - rect.left;
    sz->cy = rect.bottom - rect.top;
}