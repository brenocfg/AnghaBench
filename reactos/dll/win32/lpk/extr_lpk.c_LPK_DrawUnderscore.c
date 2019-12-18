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
struct TYPE_3__ {int cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  SCRIPT_STRING_ANALYSIS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLayout (int /*<<< orphan*/ ) ; 
 int GetTextAlign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPointW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int LAYOUT_RTL ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  SIC_COMPLEX ; 
 int /*<<< orphan*/  SSA_GLYPHS ; 
 int /*<<< orphan*/  SSA_RTL ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ ScriptIsComplex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ScriptStringAnalyse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScriptStringCPtoX (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ScriptStringFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TA_RTLREADING ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void LPK_DrawUnderscore(HDC hdc, int x, int y, LPCWSTR str, int count, int offset)
{
    SCRIPT_STRING_ANALYSIS ssa;
    DWORD dwSSAFlags = SSA_GLYPHS;
    int prefix_x;
    int prefix_end;
    int pos;
    SIZE size;
    HPEN hpen;
    HPEN oldPen;
    HRESULT hr = S_FALSE;

    if (offset == -1)
        return;

    if (ScriptIsComplex(str, count, SIC_COMPLEX) == S_OK)
    {
        if (GetLayout(hdc) & LAYOUT_RTL || GetTextAlign(hdc) & TA_RTLREADING)
            dwSSAFlags |= SSA_RTL;

        hr = ScriptStringAnalyse(hdc, str, count, (3 * count / 2 + 16),
                                 -1, dwSSAFlags, -1, NULL, NULL, NULL, NULL, NULL, &ssa);
    }

    if (hr == S_OK)
    {
        ScriptStringCPtoX(ssa, offset, FALSE, &pos);
        prefix_x = x + pos;
        ScriptStringCPtoX(ssa, offset, TRUE, &pos);
        prefix_end = x + pos;
        ScriptStringFree(&ssa);
    }
    else
    {
        GetTextExtentPointW(hdc, str, offset, &size);
        prefix_x = x + size.cx;
        GetTextExtentPointW(hdc, str, offset + 1, &size);
        prefix_end = x + size.cx - 1;
    }
    hpen = CreatePen(PS_SOLID, 1, GetTextColor(hdc));
    oldPen = SelectObject(hdc, hpen);
    MoveToEx(hdc, prefix_x, y, NULL);
    LineTo(hdc, prefix_end, y);
    SelectObject(hdc, oldPen);
    DeleteObject(hpen);
}