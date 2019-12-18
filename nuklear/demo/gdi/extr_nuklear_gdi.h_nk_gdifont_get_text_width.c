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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_6__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ nk_handle ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  dc; } ;
struct TYPE_7__ {scalar_t__ cx; } ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ GdiFont ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ GetTextExtentPoint32W (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ _alloca (int) ; 

__attribute__((used)) static float
nk_gdifont_get_text_width(nk_handle handle, float height, const char *text, int len)
{
    GdiFont *font = (GdiFont*)handle.ptr;
    SIZE size;
    int wsize;
    WCHAR* wstr;
    if (!font || !text)
        return 0;

    wsize = MultiByteToWideChar(CP_UTF8, 0, text, len, NULL, 0);
    wstr = (WCHAR*)_alloca(wsize * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, text, len, wstr, wsize);
    if (GetTextExtentPoint32W(font->dc, wstr, wsize, &size))
        return (float)size.cx;
    return -1.0f;
}