#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int (* lexical_function ) (int const) ;
typedef  int WORD ;
typedef  int WCHAR ;
struct TYPE_14__ {size_t start; int end; } ;
struct TYPE_13__ {int fCanGlyphAlone; } ;
struct TYPE_11__ {int fClusterStart; void* uJustification; void* fZeroWidth; void* fDiacritic; } ;
struct TYPE_12__ {TYPE_1__ sva; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_2__ SCRIPT_GLYPHPROP ;
typedef  TYPE_3__ SCRIPT_CHARPROP ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  TYPE_4__ IndicSyllable ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  Indic_ParseSyllables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const*,int const,TYPE_4__**,int*,int (*) (int const),scalar_t__) ; 
 int /*<<< orphan*/  OpenType_GDEF_UpdateGlyphProps (int /*<<< orphan*/ *,int const*,int const,int*,int const,TYPE_2__*) ; 
 void* SCRIPT_JUSTIFY_BLANK ; 
 void* SCRIPT_JUSTIFY_NONE ; 
 int USP10_FindGlyphInLogClust (int*,int const,int) ; 
 int /*<<< orphan*/  UpdateClustersFromGlyphProp (int const,int const,int*,TYPE_2__*) ; 
 scalar_t__ get_GSUB_Indic2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_4__*) ; 
#define  lex_Halant 135 
#define  lex_Matra_above 134 
#define  lex_Matra_below 133 
#define  lex_Matra_post 132 
#define  lex_Matra_pre 131 
#define  lex_Modifier 130 
#define  lex_ZWJ 129 
#define  lex_ZWNJ 128 

__attribute__((used)) static void ShapeCharGlyphProp_BaseIndic( HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, const WCHAR* pwcChars, const INT cChars, const WORD* pwGlyphs, const INT cGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProp, SCRIPT_GLYPHPROP *pGlyphProp, lexical_function lexical, BOOL use_syllables, BOOL override_gsub)
{
    int i,k;

    OpenType_GDEF_UpdateGlyphProps(psc, pwGlyphs, cGlyphs, pwLogClust, cChars, pGlyphProp);
    for (i = 0; i < cGlyphs; i++)
    {
        int char_index[20];
        int char_count = 0;

        k = USP10_FindGlyphInLogClust(pwLogClust, cChars, i);
        if (k>=0)
        {
            for (; k < cChars && pwLogClust[k] == i; k++)
                char_index[char_count++] = k;
        }

        if (override_gsub)
        {
            /* Most indic scripts do not set fDiacritic or fZeroWidth */
            pGlyphProp[i].sva.fDiacritic = FALSE;
            pGlyphProp[i].sva.fZeroWidth = FALSE;
        }

        if (char_count == 0)
        {
            pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_NONE;
            continue;
        }

        if (char_count ==1 && pwcChars[char_index[0]] == 0x0020)  /* space */
        {
            pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_BLANK;
            pCharProp[char_index[0]].fCanGlyphAlone = 1;
        }
        else
            pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_NONE;

        pGlyphProp[i].sva.fClusterStart = 0;
        for (k = 0; k < char_count && !pGlyphProp[i].sva.fClusterStart; k++)
            switch (lexical(pwcChars[char_index[k]]))
            {
                case lex_Matra_pre:
                case lex_Matra_post:
                case lex_Matra_above:
                case lex_Matra_below:
                case lex_Modifier:
                case lex_Halant:
                    break;
                case lex_ZWJ:
                case lex_ZWNJ:
                    /* check for dangling joiners */
                    if (pwcChars[char_index[k]-1] == 0x0020 || pwcChars[char_index[k]+1] == 0x0020)
                        pGlyphProp[i].sva.fClusterStart = 1;
                    else
                        k = char_count;
                    break;
                default:
                    pGlyphProp[i].sva.fClusterStart = 1;
                    break;
            }
    }

    if (use_syllables)
    {
        IndicSyllable *syllables = NULL;
        int syllable_count = 0;
        BOOL modern = get_GSUB_Indic2(psa, psc);

        Indic_ParseSyllables( hdc, psa, psc, pwcChars, cChars, &syllables, &syllable_count, lexical, modern);

        for (i = 0; i < syllable_count; i++)
        {
            int j;
            WORD g = pwLogClust[syllables[i].start];
            for (j = syllables[i].start+1; j <= syllables[i].end; j++)
            {
                if (pwLogClust[j] != g)
                {
                    pGlyphProp[pwLogClust[j]].sva.fClusterStart = 0;
                    pwLogClust[j] = g;
                }
            }
        }

        heap_free(syllables);
    }

    UpdateClustersFromGlyphProp(cGlyphs, cChars, pwLogClust, pGlyphProp);
}