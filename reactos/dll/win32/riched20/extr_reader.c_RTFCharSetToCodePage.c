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
struct TYPE_3__ {int ciACP; } ;
typedef  int /*<<< orphan*/  RTF_Info ;
typedef  int DWORD ;
typedef  TYPE_1__ CHARSETINFO ;

/* Variables and functions */
#define  ANSI_CHARSET 146 
#define  ARABIC_CHARSET 145 
#define  BALTIC_CHARSET 144 
#define  CHINESEBIG5_CHARSET 143 
 int CP_ACP ; 
 int CP_MACCP ; 
 int CP_OEMCP ; 
 int CP_SYMBOL ; 
#define  DEFAULT_CHARSET 142 
#define  EASTEUROPE_CHARSET 141 
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  GB2312_CHARSET 140 
#define  GREEK_CHARSET 139 
#define  HANGEUL_CHARSET 138 
#define  HEBREW_CHARSET 137 
#define  JOHAB_CHARSET 136 
#define  MAC_CHARSET 135 
#define  OEM_CHARSET 134 
#define  RUSSIAN_CHARSET 133 
#define  SHIFTJIS_CHARSET 132 
#define  SYMBOL_CHARSET 131 
 int /*<<< orphan*/  TCI_SRCCHARSET ; 
#define  THAI_CHARSET 130 
#define  TURKISH_CHARSET 129 
 int /*<<< orphan*/  TranslateCharsetInfo (int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  VIETNAMESE_CHARSET 128 

int
RTFCharSetToCodePage(RTF_Info *info, int charset)
{
	switch (charset)
        {
                case ANSI_CHARSET:
                        return 1252;
                case DEFAULT_CHARSET:
                        return CP_ACP;
                case SYMBOL_CHARSET:
                        return CP_SYMBOL;
                case MAC_CHARSET:
                        return CP_MACCP;
                case SHIFTJIS_CHARSET:
                        return 932;
                case HANGEUL_CHARSET:
                        return 949;
                case JOHAB_CHARSET:
                        return 1361;
                case GB2312_CHARSET:
                        return 936;
                case CHINESEBIG5_CHARSET:
                        return 950;
                case GREEK_CHARSET:
                        return 1253;
                case TURKISH_CHARSET:
                        return 1254;
                case VIETNAMESE_CHARSET:
                        return 1258;
                case HEBREW_CHARSET:
                        return 1255;
                case ARABIC_CHARSET:
                        return 1256;
                case BALTIC_CHARSET:
                        return 1257;
                case RUSSIAN_CHARSET:
                        return 1251;
                case THAI_CHARSET:
                        return 874;
                case EASTEUROPE_CHARSET:
                        return 1250;
                case OEM_CHARSET:
                        return CP_OEMCP;
                default:
		{
                        CHARSETINFO csi;
                        DWORD n = charset;

                        /* FIXME: TranslateCharsetInfo does not work as good as it
                         * should, so let's use it only when all else fails */
                        if (!TranslateCharsetInfo(&n, &csi, TCI_SRCCHARSET))
                                ERR("unknown charset %d\n", charset);
			else
                                return csi.ciACP;
		}
	}
        return 0;
}