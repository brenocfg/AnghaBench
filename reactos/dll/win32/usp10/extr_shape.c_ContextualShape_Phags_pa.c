#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ WCHAR ;
struct TYPE_9__ {scalar_t__ fRTL; int /*<<< orphan*/  fLogicalOrder; } ;
struct TYPE_8__ {int /*<<< orphan*/  GSUB_Table; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  TYPE_2__ SCRIPT_ANALYSIS ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int GSUB_E_NOGLYPH ; 
 int /*<<< orphan*/  UpdateClusters (int,int,int,int,int /*<<< orphan*/ *) ; 
 int Xl ; 
 int Xm ; 
 int Xn ; 
 int Xr ; 
 int apply_GSUB_feature_to_glyph (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * contextual_features ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 int /*<<< orphan*/  load_ot_tables (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ neighbour_char (int,int,scalar_t__*,int) ; 
 scalar_t__ phags_pa_CANDRABINDU ; 
 scalar_t__ phags_pa_END ; 
 scalar_t__ phags_pa_START ; 

__attribute__((used)) static void ContextualShape_Phags_pa(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwcChars, INT cChars, WORD* pwOutGlyphs, INT* pcGlyphs, INT cMaxGlyphs, WORD *pwLogClust)
{
    INT *context_shape;
    INT dirR, dirL;
    int i;
    int char_index;
    int glyph_index;

    if (*pcGlyphs != cChars)
    {
        ERR("Number of Glyphs and Chars need to match at the beginning\n");
        return;
    }

    if (!psa->fLogicalOrder && psa->fRTL)
    {
        dirR = 1;
        dirL = -1;
    }
    else
    {
        dirR = -1;
        dirL = 1;
    }

    load_ot_tables(hdc, psc);

    if (!psc->GSUB_Table)
        return;

    context_shape = heap_alloc(cChars * sizeof(*context_shape));

    for (i = 0; i < cChars; i++)
    {
        if (pwcChars[i] >= phags_pa_START && pwcChars[i] <=  phags_pa_END)
        {
            WCHAR rchar = neighbour_char(i,dirR,pwcChars,cChars);
            WCHAR lchar = neighbour_char(i,dirL,pwcChars,cChars);
            BOOL jrchar = (rchar != phags_pa_CANDRABINDU && rchar >= phags_pa_START && rchar <=  phags_pa_END);
            BOOL jlchar = (lchar != phags_pa_CANDRABINDU && lchar >= phags_pa_START && lchar <=  phags_pa_END);

            if (jrchar && jlchar)
                context_shape[i] = Xm;
            else if (jrchar)
                context_shape[i] = Xr;
            else if (jlchar)
                context_shape[i] = Xl;
            else
                context_shape[i] = Xn;
        }
        else
            context_shape[i] = -1;
    }

    /* Contextual Shaping */
    if (dirL > 0)
        char_index = glyph_index = 0;
    else
        char_index = glyph_index = cChars-1;

    while(char_index < cChars && char_index >= 0)
    {
        if (context_shape[char_index] >= 0)
        {
            INT nextIndex;
            INT prevCount = *pcGlyphs;
            nextIndex = apply_GSUB_feature_to_glyph(hdc, psa, psc, pwOutGlyphs, glyph_index, dirL, pcGlyphs, contextual_features[context_shape[char_index]]);

            if (nextIndex > GSUB_E_NOGLYPH)
            {
                UpdateClusters(nextIndex, *pcGlyphs - prevCount, dirL, cChars, pwLogClust);
                glyph_index = nextIndex;
                char_index += dirL;
            }
            else
            {
                char_index += dirL;
                glyph_index += dirL;
            }
        }
        else
        {
            char_index += dirL;
            glyph_index += dirL;
        }
    }

    heap_free(context_shape);
}