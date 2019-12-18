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
typedef  int WORD ;
typedef  int /*<<< orphan*/  MUI_SUBFONT ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * ChineseSimplifiedFonts ; 
 int /*<<< orphan*/ * ChineseTraditionalFonts ; 
 int /*<<< orphan*/ * CyrillicFonts ; 
 int /*<<< orphan*/  DebugBreak () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GreekFonts ; 
 int /*<<< orphan*/ * HebrewFonts ; 
 int /*<<< orphan*/ * JapaneseFonts ; 
 int /*<<< orphan*/ * KoreanFonts ; 
 int LANGIDFROMLCID (int /*<<< orphan*/ ) ; 
#define  LANG_ARABIC 162 
#define  LANG_ARMENIAN 161 
#define  LANG_AZERI 160 
#define  LANG_BELARUSIAN 159 
#define  LANG_BENGALI 158 
#define  LANG_BULGARIAN 157 
#define  LANG_CHINESE 156 
#define  LANG_FARSI 155 
#define  LANG_GEORGIAN 154 
#define  LANG_GREEK 153 
#define  LANG_GUJARATI 152 
#define  LANG_HEBREW 151 
#define  LANG_HINDI 150 
#define  LANG_JAPANESE 149 
#define  LANG_KAZAK 148 
#define  LANG_KONKANI 147 
#define  LANG_KOREAN 146 
#define  LANG_MARATHI 145 
#define  LANG_PUNJABI 144 
#define  LANG_RUSSIAN 143 
#define  LANG_SANSKRIT 142 
#define  LANG_SERBIAN 141 
#define  LANG_TAMIL 140 
#define  LANG_TATAR 139 
#define  LANG_TELUGU 138 
#define  LANG_THAI 137 
#define  LANG_UKRAINIAN 136 
#define  LANG_URDU 135 
#define  LANG_UZBEK 134 
#define  LANG_VIETNAMESE 133 
 int /*<<< orphan*/ * LatinFonts ; 
 int PRIMARYLANGID (int) ; 
 int SUBLANGID (int) ; 
#define  SUBLANG_CHINESE_HONGKONG 132 
#define  SUBLANG_CHINESE_MACAU 131 
#define  SUBLANG_CHINESE_SIMPLIFIED 130 
#define  SUBLANG_CHINESE_SINGAPORE 129 
#define  SUBLANG_CHINESE_TRADITIONAL 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * UnicodeFonts ; 
 int /*<<< orphan*/  UpdateRegistryForFontSubstitutes (int /*<<< orphan*/ *) ; 

BOOL
InputList_SetFontSubstitutes(LCID dwLocaleId)
{
    MUI_SUBFONT *pSubstitutes;
    WORD wLangID, wPrimaryLangID, wSubLangID;

    wLangID = LANGIDFROMLCID(dwLocaleId);
    wPrimaryLangID = PRIMARYLANGID(wLangID);
    wSubLangID = SUBLANGID(wLangID);

    /* FIXME: Add more if necessary */
    switch (wPrimaryLangID)
    {
        default:
            pSubstitutes = LatinFonts;
            break;
        case LANG_AZERI:
        case LANG_BELARUSIAN:
        case LANG_BULGARIAN:
        case LANG_KAZAK:
        case LANG_RUSSIAN:
        case LANG_SERBIAN:
        case LANG_TATAR:
        case LANG_UKRAINIAN:
        case LANG_UZBEK:
            pSubstitutes = CyrillicFonts;
            break;
        case LANG_GREEK:
            pSubstitutes = GreekFonts;
            break;
        case LANG_HEBREW:
            pSubstitutes = HebrewFonts;
            break;
        case LANG_CHINESE:
            switch (wSubLangID)
            {
                case SUBLANG_CHINESE_SIMPLIFIED:
                case SUBLANG_CHINESE_SINGAPORE:
                case SUBLANG_CHINESE_MACAU:
                    pSubstitutes = ChineseSimplifiedFonts;
                    break;
                case SUBLANG_CHINESE_TRADITIONAL:
                case SUBLANG_CHINESE_HONGKONG:
                    pSubstitutes = ChineseTraditionalFonts;
                    break;
                default:
                    pSubstitutes = NULL;
                    DebugBreak();
                    break;
            }
            break;
        case LANG_JAPANESE:
            pSubstitutes = JapaneseFonts;
            break;
        case LANG_KOREAN:
            pSubstitutes = KoreanFonts;
            break;
        case LANG_ARABIC:
        case LANG_ARMENIAN:
        case LANG_BENGALI:
        case LANG_FARSI:
        case LANG_GEORGIAN:
        case LANG_GUJARATI:
        case LANG_HINDI:
        case LANG_KONKANI:
        case LANG_MARATHI:
        case LANG_PUNJABI:
        case LANG_SANSKRIT:
        case LANG_TAMIL:
        case LANG_TELUGU:
        case LANG_THAI:
        case LANG_URDU:
        case LANG_VIETNAMESE:
            pSubstitutes = UnicodeFonts;
            break;
    }

    if (pSubstitutes)
    {
        UpdateRegistryForFontSubstitutes(pSubstitutes);
        return TRUE;
    }
    return FALSE;
}