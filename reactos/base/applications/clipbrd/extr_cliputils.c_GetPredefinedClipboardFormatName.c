#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CF_BITMAP 157 
#define  CF_DIB 156 
#define  CF_DIBV5 155 
#define  CF_DIF 154 
#define  CF_ENHMETAFILE 153 
#define  CF_HDROP 152 
#define  CF_LOCALE 151 
#define  CF_METAFILEPICT 150 
#define  CF_OEMTEXT 149 
#define  CF_PALETTE 148 
#define  CF_PENDATA 147 
#define  CF_RIFF 146 
#define  CF_SYLK 145 
#define  CF_TEXT 144 
#define  CF_TIFF 143 
#define  CF_UNICODETEXT 142 
#define  CF_WAVE 141 
 int LoadStringA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int LoadStringW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
#define  STRING_CF_BITMAP 140 
#define  STRING_CF_DIB 139 
#define  STRING_CF_DIBV5 138 
#define  STRING_CF_DIF 137 
#define  STRING_CF_ENHMETAFILE 136 
#define  STRING_CF_HDROP 135 
#define  STRING_CF_LOCALE 134 
#define  STRING_CF_METAFILEPICT 133 
#define  STRING_CF_OEMTEXT 132 
#define  STRING_CF_PALETTE 131 
#define  STRING_CF_SYLK 130 
#define  STRING_CF_TEXT 129 
#define  STRING_CF_UNICODETEXT 128 

__attribute__((used)) static int
GetPredefinedClipboardFormatName(HINSTANCE hInstance,
                                 UINT uFormat,
                                 BOOL Unicode,
                                 PVOID lpszFormat,
                                 UINT cch)
{
    static
    struct FORMAT_NAME
    {
        UINT uFormat;
        UINT uResID;
    } uFormatList[] = {
    /* Table sorted in increasing order of CF_xxx values, please keep it this way! */
        {CF_TEXT        , STRING_CF_TEXT        },          // 1
        {CF_BITMAP      , STRING_CF_BITMAP      },          // 2
        {CF_METAFILEPICT, STRING_CF_METAFILEPICT},          // 3
        {CF_SYLK        , STRING_CF_SYLK        },          // 4
        {CF_DIF         , STRING_CF_DIF         },          // 5
        {CF_TIFF        , 0/*STRING_CF_TIFF*/        },          // 6
        {CF_OEMTEXT     , STRING_CF_OEMTEXT     },          // 7
        {CF_DIB         , STRING_CF_DIB         },          // 8
        {CF_PALETTE     , STRING_CF_PALETTE     },          // 9
        {CF_PENDATA     , 0/*STRING_CF_PENDATA*/     },          // 10
        {CF_RIFF        , 0/*STRING_CF_RIFF*/        },          // 11
        {CF_WAVE        , 0/*STRING_CF_WAVE*/        },          // 12
        {CF_UNICODETEXT , STRING_CF_UNICODETEXT },          // 13
        {CF_ENHMETAFILE , STRING_CF_ENHMETAFILE },          // 14
#if(WINVER >= 0x0400)
        {CF_HDROP       , STRING_CF_HDROP       },          // 15
        {CF_LOCALE      , STRING_CF_LOCALE      },          // 16
#endif
#if(WINVER >= 0x0500)
        {CF_DIBV5       , STRING_CF_DIBV5       },          // 17
#endif
    };

    switch (uFormat)
    {
        case CF_TEXT: case CF_BITMAP: case CF_METAFILEPICT:
        case CF_SYLK: case CF_DIF: // case CF_TIFF:
        case CF_OEMTEXT: case CF_DIB: case CF_PALETTE:
        // case CF_PENDATA: // case CF_RIFF: // case CF_WAVE:
        case CF_UNICODETEXT: case CF_ENHMETAFILE:
#if(WINVER >= 0x0400)
        case CF_HDROP: case CF_LOCALE:
#endif
#if(WINVER >= 0x0500)
        case CF_DIBV5:
#endif
        {
            if (Unicode)
                return LoadStringW(hInstance, uFormatList[uFormat-1].uResID, (LPWSTR)lpszFormat, cch);
            else
                return LoadStringA(hInstance, uFormatList[uFormat-1].uResID, (LPSTR)lpszFormat, cch);
        }

        default:
        {
            return 0;
        }
    }
}