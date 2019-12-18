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
typedef  int /*<<< orphan*/  WORD ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int IndicSyllable ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Bengali_consonants ; 
 int /*<<< orphan*/  Bengali_vowels ; 
 int /*<<< orphan*/  ComposeConsonants (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DecomposeVowels (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetGlyphIndicesW (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Indic_ReorderCharacters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Reorder_Like_Bengali ; 
 int /*<<< orphan*/  ShapeIndicSyllables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  apply_GSUB_feature_to_glyph (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,char*) ; 
 int /*<<< orphan*/  bengali_lex ; 
 int /*<<< orphan*/  debugstr_wn (int*,int) ; 
 int /*<<< orphan*/  get_GSUB_Indic2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void ContextualShape_Bengali(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwcChars, INT cChars, WORD* pwOutGlyphs, INT* pcGlyphs, INT cMaxGlyphs, WORD *pwLogClust)
{
    int cCount = cChars;
    WCHAR *input;
    IndicSyllable *syllables = NULL;
    int syllable_count = 0;
    BOOL modern = get_GSUB_Indic2(psa, psc);

    if (*pcGlyphs != cChars)
    {
        ERR("Number of Glyphs and Chars need to match at the beginning\n");
        return;
    }

    input = heap_alloc(2 * cChars * sizeof(*input));
    memcpy(input, pwcChars, cChars * sizeof(WCHAR));

    /* Step 1: Decompose Vowels and Compose Consonants */
    DecomposeVowels(hdc, input,  &cCount, Bengali_vowels, pwLogClust, cChars);
    ComposeConsonants(hdc, input, &cCount, Bengali_consonants, pwLogClust);
    TRACE("New composed string %s (%i)\n",debugstr_wn(input,cCount),cCount);

    /* Step 2: Reorder within Syllables */
    Indic_ReorderCharacters( hdc, psa, psc, input, cCount, &syllables, &syllable_count, bengali_lex, Reorder_Like_Bengali, modern);
    TRACE("reordered string %s\n",debugstr_wn(input,cCount));
    GetGlyphIndicesW(hdc, input, cCount, pwOutGlyphs, 0);
    *pcGlyphs = cCount;

    /* Step 3: Initial form is only applied to the beginning of words */
    for (cCount = cCount - 1 ; cCount >= 0; cCount --)
    {
        if (cCount == 0 || input[cCount] == 0x0020) /* space */
        {
            int index = cCount;
            int gCount = 1;
            if (index > 0) index++;

            apply_GSUB_feature_to_glyph(hdc, psa, psc, &pwOutGlyphs[index], 0, 1, &gCount, "init");
        }
    }

    /* Step 4: Base Form application to syllables */
    ShapeIndicSyllables(hdc, psc, psa, input, cChars, syllables, syllable_count, pwOutGlyphs, pcGlyphs, pwLogClust, bengali_lex, NULL, modern);

    heap_free(input);
    heap_free(syllables);
}