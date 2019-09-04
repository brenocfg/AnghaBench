#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_8__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ nk_handle ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  format; int /*<<< orphan*/  memory; } ;
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {float member_0; float member_1; float member_2; float member_3; float Width; } ;
typedef  TYPE_2__ RectF ;
typedef  TYPE_3__ GdipFont ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  GdipMeasureString (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ _alloca (int) ; 
 TYPE_5__ gdip ; 

__attribute__((used)) static float
nk_gdipfont_get_text_width(nk_handle handle, float height, const char *text, int len)
{
    GdipFont *font = (GdipFont *)handle.ptr;
    RectF layout = { 0.0f, 0.0f, 65536.0f, 65536.0f };
    RectF bbox;
    int wsize;
    WCHAR* wstr;
    if (!font || !text)
        return 0;

    (void)height;
    wsize = MultiByteToWideChar(CP_UTF8, 0, text, len, NULL, 0);
    wstr = (WCHAR*)_alloca(wsize * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, text, len, wstr, wsize);

    GdipMeasureString(gdip.memory, wstr, wsize, font->handle, &layout, gdip.format, &bbox, NULL, NULL);
    return bbox.Width;
}