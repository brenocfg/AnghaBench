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
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  TYPE_1__ GdipFont ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  FontStyleRegular ; 
 int /*<<< orphan*/  GdipCreateFont (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateFontFamilyFromName (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  UnitPixel ; 
 scalar_t__ _alloca (int) ; 
 scalar_t__ calloc (int,int) ; 

GdipFont*
nk_gdipfont_create(const char *name, int size)
{
    GdipFont *font = (GdipFont*)calloc(1, sizeof(GdipFont));
    GpFontFamily *family;

    int wsize = MultiByteToWideChar(CP_UTF8, 0, name, -1, NULL, 0);
    WCHAR* wname = (WCHAR*)_alloca((wsize + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, name, -1, wname, wsize);
    wname[wsize] = 0;

    GdipCreateFontFamilyFromName(wname, NULL, &family);
    GdipCreateFont(family, (REAL)size, FontStyleRegular, UnitPixel, &font->handle);
    GdipDeleteFontFamily(family);

    return font;
}