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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  IndicSyllable ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ComposeConsonants (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DecomposeVowels (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetGlyphIndicesW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Indic_ReorderCharacters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Reorder_Like_Bengali ; 
 int /*<<< orphan*/  SecondReorder_Like_Tamil ; 
 int /*<<< orphan*/  ShapeIndicSyllables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  Tamil_consonants ; 
 int /*<<< orphan*/  Tamil_vowels ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_GSUB_Indic2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tamil_lex ; 

__attribute__((used)) static void ContextualShape_Tamil(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwcChars, INT cChars, WORD* pwOutGlyphs, INT* pcGlyphs, INT cMaxGlyphs, WORD *pwLogClust)
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
    DecomposeVowels(hdc, input,  &cCount, Tamil_vowels, pwLogClust, cChars);
    ComposeConsonants(hdc, input, &cCount, Tamil_consonants, pwLogClust);
    TRACE("New composed string %s (%i)\n",debugstr_wn(input,cCount),cCount);

    /* Step 2: Reorder within Syllables */
    Indic_ReorderCharacters( hdc, psa, psc, input, cCount, &syllables, &syllable_count, tamil_lex, Reorder_Like_Bengali, modern);
    TRACE("reordered string %s\n",debugstr_wn(input,cCount));
    GetGlyphIndicesW(hdc, input, cCount, pwOutGlyphs, 0);
    *pcGlyphs = cCount;

    /* Step 3: Base Form application to syllables */
    ShapeIndicSyllables(hdc, psc, psa, input, cChars, syllables, syllable_count, pwOutGlyphs, pcGlyphs, pwLogClust, tamil_lex, SecondReorder_Like_Tamil, modern);

    heap_free(input);
    heap_free(syllables);
}