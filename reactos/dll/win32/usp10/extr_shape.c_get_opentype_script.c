#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_10__ {scalar_t__ newOtTag; } ;
struct TYPE_9__ {scalar_t__ scriptTag; } ;
struct TYPE_8__ {size_t eScript; } ;
struct TYPE_7__ {scalar_t__ userScript; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  TYPE_2__ SCRIPT_ANALYSIS ;
typedef  scalar_t__ OPENTYPE_TAG ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  ANSI_CHARSET 142 
#define  ARABIC_CHARSET 141 
#define  BALTIC_CHARSET 140 
#define  CHINESEBIG5_CHARSET 139 
#define  EASTEUROPE_CHARSET 138 
#define  GB2312_CHARSET 137 
#define  GREEK_CHARSET 136 
 int GetTextCharsetInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
#define  HANGUL_CHARSET 135 
#define  HEBREW_CHARSET 134 
#define  JOHAB_CHARSET 133 
 scalar_t__ MS_MAKE_TAG (char,char,char,char) ; 
#define  RUSSIAN_CHARSET 132 
#define  SHIFTJIS_CHARSET 131 
 TYPE_6__* ShapingData ; 
#define  THAI_CHARSET 130 
#define  TURKISH_CHARSET 129 
#define  VIETNAMESE_CHARSET 128 
 TYPE_3__* scriptInformation ; 

__attribute__((used)) static OPENTYPE_TAG get_opentype_script(HDC hdc, const SCRIPT_ANALYSIS *psa,
        const ScriptCache *script_cache, BOOL try_new)
{
    UINT charset;

    if (script_cache->userScript)
    {
        if (try_new && ShapingData[psa->eScript].newOtTag
                && script_cache->userScript == scriptInformation[psa->eScript].scriptTag)
            return ShapingData[psa->eScript].newOtTag;

        return script_cache->userScript;
    }

    if (try_new && ShapingData[psa->eScript].newOtTag)
        return ShapingData[psa->eScript].newOtTag;

    if (scriptInformation[psa->eScript].scriptTag)
        return scriptInformation[psa->eScript].scriptTag;

    /*
     * fall back to the font charset
     */
    charset = GetTextCharsetInfo(hdc, NULL, 0x0);
    switch (charset)
    {
        case ANSI_CHARSET:
        case BALTIC_CHARSET: return MS_MAKE_TAG('l','a','t','n');
        case CHINESEBIG5_CHARSET: return MS_MAKE_TAG('h','a','n','i');
        case EASTEUROPE_CHARSET: return MS_MAKE_TAG('l','a','t','n'); /* ?? */
        case GB2312_CHARSET: return MS_MAKE_TAG('h','a','n','i');
        case GREEK_CHARSET: return MS_MAKE_TAG('g','r','e','k');
        case HANGUL_CHARSET: return MS_MAKE_TAG('h','a','n','g');
        case RUSSIAN_CHARSET: return MS_MAKE_TAG('c','y','r','l');
        case SHIFTJIS_CHARSET: return MS_MAKE_TAG('k','a','n','a');
        case TURKISH_CHARSET: return MS_MAKE_TAG('l','a','t','n'); /* ?? */
        case VIETNAMESE_CHARSET: return MS_MAKE_TAG('l','a','t','n');
        case JOHAB_CHARSET: return MS_MAKE_TAG('l','a','t','n'); /* ?? */
        case ARABIC_CHARSET: return MS_MAKE_TAG('a','r','a','b');
        case HEBREW_CHARSET: return MS_MAKE_TAG('h','e','b','r');
        case THAI_CHARSET: return MS_MAKE_TAG('t','h','a','i');
        default: return MS_MAKE_TAG('l','a','t','n');
    }
}