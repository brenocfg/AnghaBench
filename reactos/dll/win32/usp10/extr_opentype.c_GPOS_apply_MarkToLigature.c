#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_24__ {int /*<<< orphan*/ * LigatureAnchor; } ;
struct TYPE_23__ {int /*<<< orphan*/ * LigatureAttach; int /*<<< orphan*/  LigatureCount; } ;
struct TYPE_22__ {scalar_t__ ComponentRecord; int /*<<< orphan*/  ComponentCount; } ;
struct TYPE_21__ {TYPE_4__* MarkRecord; int /*<<< orphan*/  MarkCount; } ;
struct TYPE_20__ {int /*<<< orphan*/  PosFormat; int /*<<< orphan*/  LigatureArray; int /*<<< orphan*/  MarkArray; int /*<<< orphan*/  ClassCount; int /*<<< orphan*/  LigatureCoverage; int /*<<< orphan*/  MarkCoverage; } ;
struct TYPE_19__ {int /*<<< orphan*/  MarkAnchor; int /*<<< orphan*/  Class; } ;
struct TYPE_18__ {int /*<<< orphan*/  SubTableCount; } ;
struct TYPE_17__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_16__ {int /*<<< orphan*/  fLogicalOrder; scalar_t__ fRTL; } ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__ OT_LookupTable ;
typedef  TYPE_4__ GPOS_MarkRecord ;
typedef  TYPE_5__ GPOS_MarkLigPosFormat1 ;
typedef  TYPE_6__ GPOS_MarkArray ;
typedef  TYPE_7__ GPOS_LigatureAttach ;
typedef  TYPE_8__ GPOS_LigatureArray ;
typedef  TYPE_9__ GPOS_ComponentRecord ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPOS_get_anchor_values (int /*<<< orphan*/  const*,TYPE_2__*,unsigned int) ; 
 scalar_t__ GPOS_get_subtable (TYPE_3__ const*,int) ; 
 int GSUB_is_glyph_covered (int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_point (TYPE_2__*) ; 

__attribute__((used)) static void GPOS_apply_MarkToLigature(const OT_LookupTable *look, const SCRIPT_ANALYSIS *analysis,
        const WORD *glyphs, unsigned int glyph_index, unsigned int glyph_count, unsigned int ppem, POINT *pt)
{
    int j;
    int write_dir = (analysis->fRTL && !analysis->fLogicalOrder) ? -1 : 1;

    TRACE("MarkToLigature Attachment Positioning Subtable\n");

    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        const GPOS_MarkLigPosFormat1 *mlpf1 = (const GPOS_MarkLigPosFormat1 *)GPOS_get_subtable(look, j);
        if (GET_BE_WORD(mlpf1->PosFormat) == 1)
        {
            int offset = GET_BE_WORD(mlpf1->MarkCoverage);
            int mark_index;
            mark_index = GSUB_is_glyph_covered((const BYTE*)mlpf1+offset, glyphs[glyph_index]);
            if (mark_index != -1)
            {
                int ligature_index;
                offset = GET_BE_WORD(mlpf1->LigatureCoverage);
                ligature_index = GSUB_is_glyph_covered((const BYTE*)mlpf1+offset, glyphs[glyph_index - write_dir]);
                if (ligature_index != -1)
                {
                    const GPOS_MarkArray *ma;
                    const GPOS_MarkRecord *mr;

                    const GPOS_LigatureArray *la;
                    const GPOS_LigatureAttach *lt;
                    int mark_class;
                    int class_count = GET_BE_WORD(mlpf1->ClassCount);
                    int component_count;
                    int component_size;
                    int i;
                    POINT ligature_pt;
                    POINT mark_pt;

                    TRACE("Mark %x(%i) and ligature %x(%i)\n",glyphs[glyph_index], mark_index, glyphs[glyph_index - write_dir], ligature_index);
                    offset = GET_BE_WORD(mlpf1->MarkArray);
                    ma = (const GPOS_MarkArray*)((const BYTE*)mlpf1 + offset);
                    if (mark_index > GET_BE_WORD(ma->MarkCount))
                    {
                        ERR("Mark index exceeded mark count\n");
                        return;
                    }
                    mr = &ma->MarkRecord[mark_index];
                    mark_class = GET_BE_WORD(mr->Class);
                    TRACE("Mark Class %i total classes %i\n",mark_class,class_count);
                    offset = GET_BE_WORD(mlpf1->LigatureArray);
                    la = (const GPOS_LigatureArray*)((const BYTE*)mlpf1 + offset);
                    if (ligature_index > GET_BE_WORD(la->LigatureCount))
                    {
                        ERR("Ligature index exceeded ligature count\n");
                        return;
                    }
                    offset = GET_BE_WORD(la->LigatureAttach[ligature_index]);
                    lt = (const GPOS_LigatureAttach*)((const BYTE*)la + offset);

                    component_count = GET_BE_WORD(lt->ComponentCount);
                    component_size = class_count * sizeof(WORD);
                    offset = 0;
                    for (i = 0; i < component_count && !offset; i++)
                    {
                        int k;
                        const GPOS_ComponentRecord *cr = (const GPOS_ComponentRecord*)((const BYTE*)lt->ComponentRecord + (component_size * i));
                        for (k = 0; k < class_count && !offset; k++)
                            offset = GET_BE_WORD(cr->LigatureAnchor[k]);
                        cr = (const GPOS_ComponentRecord*)((const BYTE*)cr + component_size);
                    }
                    if (!offset)
                    {
                        ERR("Failed to find available ligature connection point\n");
                        return;
                    }

                    GPOS_get_anchor_values((const BYTE*)lt + offset, &ligature_pt, ppem);
                    offset = GET_BE_WORD(mr->MarkAnchor);
                    GPOS_get_anchor_values((const BYTE*)ma + offset, &mark_pt, ppem);
                    TRACE("Offset on ligature is %s design units\n",wine_dbgstr_point(&ligature_pt));
                    TRACE("Offset on mark is %s design units\n",wine_dbgstr_point(&mark_pt));
                    pt->x += ligature_pt.x - mark_pt.x;
                    pt->y += ligature_pt.y - mark_pt.y;
                    TRACE("Resulting cumulative offset is %s design units\n",wine_dbgstr_point(pt));
                }
            }
        }
        else
            FIXME("Unhandled Mark To Ligature Format %i\n",GET_BE_WORD(mlpf1->PosFormat));
    }
}