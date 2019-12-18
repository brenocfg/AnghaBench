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
typedef  int /*<<< orphan*/  attr ;
typedef  char WCHAR ;
struct TYPE_3__ {char* lfFaceName; int lfHeight; void* lfStrikeOut; void* lfUnderline; void* lfItalic; int /*<<< orphan*/  lfWeight; int /*<<< orphan*/  lfCharSet; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ LOGFONTW ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int /*<<< orphan*/  E_PROP_ID_UNSUPPORTED ; 
 int /*<<< orphan*/  FW_BOLD ; 
 int /*<<< orphan*/  FW_REGULAR ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LF_FACESIZE ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  MSSTYLES_GetNextInteger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ MSSTYLES_GetNextToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int MulDiv (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  lstrcmpiW (char const*,char*) ; 

__attribute__((used)) static HRESULT MSSTYLES_GetFont (LPCWSTR lpCur, LPCWSTR lpEnd,
                                 LPCWSTR *lpValEnd, LOGFONTW* pFont)
{
    static const WCHAR szBold[] = {'b','o','l','d','\0'};
    static const WCHAR szItalic[] = {'i','t','a','l','i','c','\0'};
    static const WCHAR szUnderline[] = {'u','n','d','e','r','l','i','n','e','\0'};
    static const WCHAR szStrikeOut[] = {'s','t','r','i','k','e','o','u','t','\0'};
    int pointSize;
    WCHAR attr[32];

    if(!MSSTYLES_GetNextToken(lpCur, lpEnd, &lpCur, pFont->lfFaceName, LF_FACESIZE)) {
        TRACE("Property is there, but failed to get face name\n");
        *lpValEnd = lpCur;
        return E_PROP_ID_UNSUPPORTED;
    }
    if(!MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &pointSize)) {
        TRACE("Property is there, but failed to get point size\n");
        *lpValEnd = lpCur;
        return E_PROP_ID_UNSUPPORTED;
    }
    if(pointSize > 0)
    {
        HDC hdc = GetDC(0);
        pointSize = -MulDiv(pointSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
        ReleaseDC(0, hdc);
    }

    pFont->lfHeight = pointSize;
    pFont->lfWeight = FW_REGULAR;
    pFont->lfCharSet = DEFAULT_CHARSET;
    while(MSSTYLES_GetNextToken(lpCur, lpEnd, &lpCur, attr, sizeof(attr)/sizeof(attr[0]))) {
        if(!lstrcmpiW(szBold, attr)) pFont->lfWeight = FW_BOLD;
        else if(!lstrcmpiW(szItalic, attr)) pFont->lfItalic = TRUE;
        else if(!lstrcmpiW(szUnderline, attr)) pFont->lfUnderline = TRUE;
        else if(!lstrcmpiW(szStrikeOut, attr)) pFont->lfStrikeOut = TRUE;
    }
    *lpValEnd = lpCur;
    return S_OK;
}