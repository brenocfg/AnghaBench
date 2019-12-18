#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_10__ {int /*<<< orphan*/  LigGlyph; int /*<<< orphan*/ * Component; int /*<<< orphan*/  CompCount; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Ligature; int /*<<< orphan*/  LigatureCount; } ;
struct TYPE_8__ {int /*<<< orphan*/ * LigatureSet; int /*<<< orphan*/  Coverage; } ;
struct TYPE_7__ {int /*<<< orphan*/  SubTableCount; } ;
typedef  TYPE_1__ OT_LookupTable ;
typedef  size_t INT ;
typedef  TYPE_2__ GSUB_LigatureSubstFormat1 ;
typedef  TYPE_3__ GSUB_LigatureSet ;
typedef  TYPE_4__ GSUB_Ligature ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 size_t GSUB_E_NOGLYPH ; 
 scalar_t__ GSUB_get_subtable (TYPE_1__ const*,int) ; 
 int GSUB_is_glyph_covered (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  memmove (int*,int*,size_t) ; 

__attribute__((used)) static INT GSUB_apply_LigatureSubst(const OT_LookupTable *look, WORD *glyphs, INT glyph_index, INT write_dir, INT *glyph_count)
{
    int j;

    TRACE("Ligature Substitution Subtable\n");
    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        const GSUB_LigatureSubstFormat1 *lsf1;
        int offset,index;

        lsf1 = (const GSUB_LigatureSubstFormat1*)GSUB_get_subtable(look, j);
        offset = GET_BE_WORD(lsf1->Coverage);
        index = GSUB_is_glyph_covered((const BYTE*)lsf1+offset, glyphs[glyph_index]);
        TRACE("  Coverage index %i\n",index);
        if (index != -1)
        {
            const GSUB_LigatureSet *ls;
            int k, count;

            offset = GET_BE_WORD(lsf1->LigatureSet[index]);
            ls = (const GSUB_LigatureSet*)((const BYTE*)lsf1+offset);
            count = GET_BE_WORD(ls->LigatureCount);
            TRACE("  LigatureSet has %i members\n",count);
            for (k = 0; k < count; k++)
            {
                const GSUB_Ligature *lig;
                int CompCount,l,CompIndex;

                offset = GET_BE_WORD(ls->Ligature[k]);
                lig = (const GSUB_Ligature*)((const BYTE*)ls+offset);
                CompCount = GET_BE_WORD(lig->CompCount) - 1;
                CompIndex = glyph_index+write_dir;
                for (l = 0; l < CompCount && CompIndex >= 0 && CompIndex < *glyph_count; l++)
                {
                    int CompGlyph;
                    CompGlyph = GET_BE_WORD(lig->Component[l]);
                    if (CompGlyph != glyphs[CompIndex])
                        break;
                    CompIndex += write_dir;
                }
                if (l == CompCount)
                {
                    int replaceIdx = glyph_index;
                    if (write_dir < 0)
                        replaceIdx = glyph_index - CompCount;

                    TRACE("    Glyph is 0x%x (+%i) ->",glyphs[glyph_index],CompCount);
                    glyphs[replaceIdx] = GET_BE_WORD(lig->LigGlyph);
                    TRACE("0x%x\n",glyphs[replaceIdx]);
                    if (CompCount > 0)
                    {
                        unsigned int j = replaceIdx + 1;
                        memmove(&glyphs[j], &glyphs[j + CompCount], (*glyph_count - j) * sizeof(*glyphs));
                        *glyph_count = *glyph_count - CompCount;
                    }
                    return replaceIdx + write_dir;
                }
            }
        }
    }
    return GSUB_E_NOGLYPH;
}