#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* second_reorder_function ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  lexical_function ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_18__ {int end; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  LoadedFeature ;
typedef  TYPE_1__ IndicSyllable ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Apply_Indic_BasicForm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Apply_Indic_PostBase (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  Apply_Indic_PreBase (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  Apply_Indic_Rphf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FEATURE_GSUB_TABLE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * load_OT_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  shift_syllable_glyph_indexs (TYPE_1__*,int,int) ; 

__attribute__((used)) static void ShapeIndicSyllables(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwChars, INT cChars, IndicSyllable *syllables, INT syllable_count, WORD *pwOutGlyphs, INT* pcGlyphs, WORD *pwLogClust, lexical_function lexical, second_reorder_function second_reorder, BOOL modern)
{
    int c;
    int overall_shift = 0;
    LoadedFeature *locl = (modern)?load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "locl"):NULL;
    LoadedFeature *nukt = load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "nukt");
    LoadedFeature *akhn = load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "akhn");
    LoadedFeature *rkrf = (modern)?load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "rkrf"):NULL;
    LoadedFeature *pstf = load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "pstf");
    LoadedFeature *vatu = (!rkrf)?load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "vatu"):NULL;
    LoadedFeature *cjct = (modern)?load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "cjct"):NULL;
    BOOL rphf = (load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "rphf") != NULL);
    BOOL pref = (load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "pref") != NULL);
    BOOL blwf = (load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "blwf") != NULL);
    BOOL half = (load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, "half") != NULL);
    IndicSyllable glyph_indexs;

    for (c = 0; c < syllable_count; c++)
    {
        int old_end;
        memcpy(&glyph_indexs, &syllables[c], sizeof(IndicSyllable));
        shift_syllable_glyph_indexs(&glyph_indexs, -1, overall_shift);
        old_end = glyph_indexs.end;

        if (locl)
        {
            TRACE("applying feature locl\n");
            Apply_Indic_BasicForm(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, locl);
        }
        if (nukt)
        {
            TRACE("applying feature nukt\n");
            Apply_Indic_BasicForm(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, nukt);
        }
        if (akhn)
        {
            TRACE("applying feature akhn\n");
            Apply_Indic_BasicForm(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, akhn);
        }

        if (rphf)
            Apply_Indic_Rphf(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs);
        if (rkrf)
        {
            TRACE("applying feature rkrf\n");
            Apply_Indic_BasicForm(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, rkrf);
        }
        if (pref)
            Apply_Indic_PostBase(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, modern, "pref");
        if (blwf)
        {
            if (!modern)
                Apply_Indic_PreBase(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, "blwf");

            Apply_Indic_PostBase(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, modern, "blwf");

        }
        if (half)
            Apply_Indic_PreBase(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, "half");
        if (pstf)
        {
            TRACE("applying feature pstf\n");
            Apply_Indic_BasicForm(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, pstf);
        }
        if (vatu)
        {
            TRACE("applying feature vatu\n");
            Apply_Indic_BasicForm(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, vatu);
        }
        if (cjct)
        {
            TRACE("applying feature cjct\n");
            Apply_Indic_BasicForm(hdc, psc, psa, pwChars, cChars, &syllables[c], pwOutGlyphs, pcGlyphs, pwLogClust, lexical, &glyph_indexs, cjct);
        }

        if (second_reorder)
            second_reorder(pwChars, &syllables[c], pwOutGlyphs, &glyph_indexs, lexical);

        overall_shift += glyph_indexs.end - old_end;
    }
}