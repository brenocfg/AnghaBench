#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfHeight; } ;
struct TYPE_6__ {int /*<<< orphan*/  tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_2__ LOGFONTW ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateFontIndirectW (TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetTextMetricsW (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  MulDiv (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static INT msi_dialog_get_sans_serif_height( HWND hwnd )
{
    static const WCHAR szSansSerif[] = {
        'M','S',' ','S','a','n','s',' ','S','e','r','i','f',0 };
    LOGFONTW lf;
    TEXTMETRICW tm;
    BOOL r;
    LONG height = 0;
    HFONT hFont, hOldFont;
    HDC hdc;

    hdc = GetDC( hwnd );
    if (hdc)
    {
        memset( &lf, 0, sizeof lf );
        lf.lfHeight = MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
        strcpyW( lf.lfFaceName, szSansSerif );
        hFont = CreateFontIndirectW(&lf);
        if (hFont)
        {
            hOldFont = SelectObject( hdc, hFont );
            r = GetTextMetricsW( hdc, &tm );
            if (r)
                height = tm.tmHeight;
            SelectObject( hdc, hOldFont );
            DeleteObject( hFont );
        }
        ReleaseDC( hwnd, hdc );
    }
    return height;
}