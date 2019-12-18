#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ userLang; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int OPENTYPE_TAG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int MS_MAKE_TAG (char,char,char,char) ; 
 int /*<<< orphan*/  OpenType_GetFontLanguageTags (TYPE_1__*,int,int,int,int*,int*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  load_ot_tables (int /*<<< orphan*/ ,TYPE_1__*) ; 

HRESULT SHAPE_GetFontLanguageTags( HDC hdc, ScriptCache *psc,
                                   SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
                                   int cMaxTags, OPENTYPE_TAG *pLangSysTags,
                                   int *pcTags)
{
    HRESULT hr;
    OPENTYPE_TAG searching = 0x00000000;
    BOOL fellback = FALSE;

    load_ot_tables(hdc, psc);

    if (psa && psc->userLang != 0)
        searching = psc->userLang;

    hr = OpenType_GetFontLanguageTags(psc, tagScript, searching, cMaxTags, pLangSysTags, pcTags);
    if (FAILED(hr))
    {
        fellback = TRUE;
        hr = OpenType_GetFontLanguageTags(psc, MS_MAKE_TAG('l','a','t','n'), searching, cMaxTags, pLangSysTags, pcTags);
    }

    if (FAILED(hr) || fellback)
        *pcTags = 0;
    if (SUCCEEDED(hr) && fellback && psa)
        hr = E_INVALIDARG;
    return hr;
}