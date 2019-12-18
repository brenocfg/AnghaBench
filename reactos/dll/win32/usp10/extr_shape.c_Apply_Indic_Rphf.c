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
typedef  int /*<<< orphan*/  lexical_function ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {scalar_t__ ralf; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  TYPE_1__ IndicSyllable ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ GSUB_E_NOGLYPH ; 
 int /*<<< orphan*/  UpdateClusters (scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ apply_GSUB_feature_to_glyph (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__*,char*) ; 
 int /*<<< orphan*/  shift_syllable_glyph_indexs (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void Apply_Indic_Rphf(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwChars, INT cChars, IndicSyllable *syllable, WORD *pwOutGlyphs, INT* pcGlyphs, WORD *pwLogClust, lexical_function lexical, IndicSyllable *glyph_index)
{
    INT nextIndex;
    INT prevCount = *pcGlyphs;

    if (syllable->ralf >= 0)
    {
        nextIndex = apply_GSUB_feature_to_glyph(hdc, psa, psc, pwOutGlyphs, glyph_index->ralf, 1, pcGlyphs, "rphf");
        if (nextIndex > GSUB_E_NOGLYPH)
        {
            UpdateClusters(nextIndex, *pcGlyphs - prevCount, 1, cChars, pwLogClust);
            shift_syllable_glyph_indexs(glyph_index,glyph_index->ralf,*pcGlyphs - prevCount);
        }
    }
}