#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_8__ ;
typedef  struct TYPE_50__   TYPE_7__ ;
typedef  struct TYPE_49__   TYPE_6__ ;
typedef  struct TYPE_48__   TYPE_5__ ;
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_1__ ;

/* Type definitions */
typedef  enum gpos_lookup_type { ____Placeholder_gpos_lookup_type } gpos_lookup_type ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_51__ {int du; int dv; } ;
struct TYPE_50__ {int /*<<< orphan*/  PosFormat; int /*<<< orphan*/  ExtensionLookupType; } ;
struct TYPE_49__ {int /*<<< orphan*/ * Lookup; } ;
struct TYPE_48__ {int /*<<< orphan*/ * SubTable; int /*<<< orphan*/  SubTableCount; int /*<<< orphan*/  LookupFlag; int /*<<< orphan*/  LookupType; } ;
struct TYPE_44__ {int tmAscent; int tmDescent; int tmInternalLeading; } ;
struct TYPE_47__ {TYPE_1__ otmTextMetrics; } ;
struct TYPE_46__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_45__ {int /*<<< orphan*/  fLogicalOrder; int /*<<< orphan*/  fRTL; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_2__ SCRIPT_ANALYSIS ;
typedef  TYPE_3__ POINT ;
typedef  TYPE_4__ OUTLINETEXTMETRICW ;
typedef  TYPE_5__ OT_LookupTable ;
typedef  TYPE_6__ OT_LookupList ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  TYPE_7__ GPOS_ExtensionPosFormat1 ;
typedef  TYPE_8__ GOFFSET ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
#define  GPOS_LOOKUP_ADJUST_PAIR 135 
#define  GPOS_LOOKUP_ADJUST_SINGLE 134 
#define  GPOS_LOOKUP_ATTACH_CURSIVE 133 
#define  GPOS_LOOKUP_ATTACH_MARK_TO_BASE 132 
#define  GPOS_LOOKUP_ATTACH_MARK_TO_LIGATURE 131 
#define  GPOS_LOOKUP_ATTACH_MARK_TO_MARK 130 
#define  GPOS_LOOKUP_POSITION_CONTEXT 129 
#define  GPOS_LOOKUP_POSITION_CONTEXT_CHAINED 128 
 int GPOS_LOOKUP_POSITION_EXTENSION ; 
 unsigned int GPOS_apply_ChainContextPos (int /*<<< orphan*/  const*,TYPE_4__ const*,int /*<<< orphan*/  const*,TYPE_2__ const*,int*,TYPE_6__ const*,TYPE_5__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,TYPE_8__*) ; 
 unsigned int GPOS_apply_ContextPos (int /*<<< orphan*/  const*,TYPE_4__ const*,int /*<<< orphan*/  const*,TYPE_2__ const*,int*,TYPE_6__ const*,TYPE_5__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,TYPE_8__*) ; 
 int /*<<< orphan*/  GPOS_apply_CursiveAttachment (TYPE_5__ const*,TYPE_2__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,int,TYPE_3__*) ; 
 int GPOS_apply_MarkToBase (int /*<<< orphan*/  const*,TYPE_5__ const*,TYPE_2__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  GPOS_apply_MarkToLigature (TYPE_5__ const*,TYPE_2__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  GPOS_apply_MarkToMark (TYPE_5__ const*,TYPE_2__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,int,TYPE_3__*) ; 
 int GPOS_apply_PairAdjustment (TYPE_5__ const*,TYPE_2__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  GPOS_apply_SingleAdjustment (TYPE_5__ const*,TYPE_2__ const*,int /*<<< orphan*/  const*,unsigned int,unsigned int,int,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  GPOS_convert_design_units_to_device (TYPE_4__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int round (double) ; 

__attribute__((used)) static unsigned int GPOS_apply_lookup(const ScriptCache *script_cache, const OUTLINETEXTMETRICW *lpotm,
        const LOGFONTW *lplogfont, const SCRIPT_ANALYSIS *analysis, int *piAdvance, const OT_LookupList *lookup,
        unsigned int lookup_index, const WORD *glyphs, unsigned int glyph_index, unsigned int glyph_count,
        GOFFSET *pGoffset)
{
    int offset;
    const OT_LookupTable *look;
    int ppem = lpotm->otmTextMetrics.tmAscent + lpotm->otmTextMetrics.tmDescent - lpotm->otmTextMetrics.tmInternalLeading;
    enum gpos_lookup_type type;

    offset = GET_BE_WORD(lookup->Lookup[lookup_index]);
    look = (const OT_LookupTable*)((const BYTE*)lookup + offset);
    type = GET_BE_WORD(look->LookupType);
    TRACE("type %#x, flag %#x, subtables %u.\n", type,
            GET_BE_WORD(look->LookupFlag), GET_BE_WORD(look->SubTableCount));

    if (type == GPOS_LOOKUP_POSITION_EXTENSION)
    {
        if (GET_BE_WORD(look->SubTableCount))
        {
            const GPOS_ExtensionPosFormat1 *ext = (const GPOS_ExtensionPosFormat1 *)((const BYTE *)look + GET_BE_WORD(look->SubTable[0]));
            if (GET_BE_WORD(ext->PosFormat) == 1)
            {
                type = GET_BE_WORD(ext->ExtensionLookupType);
                TRACE("extension type %i\n",type);
            }
            else
            {
                FIXME("Unhandled Extension Positioning Format %i\n",GET_BE_WORD(ext->PosFormat));
            }
        }
        else
        {
            WARN("lookup type is Extension Positioning but no extension subtable exists\n");
        }
    }
    switch (type)
    {
        case GPOS_LOOKUP_ADJUST_SINGLE:
        {
            double devX, devY;
            POINT adjust = {0,0};
            POINT advance = {0,0};
            GPOS_apply_SingleAdjustment(look, analysis, glyphs, glyph_index, glyph_count, ppem, &adjust, &advance);
            if (adjust.x || adjust.y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, adjust.x, adjust.y, &devX, &devY);
                pGoffset[glyph_index].du += round(devX);
                pGoffset[glyph_index].dv += round(devY);
            }
            if (advance.x || advance.y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, advance.x, advance.y, &devX, &devY);
                piAdvance[glyph_index] += round(devX);
                if (advance.y)
                    FIXME("Unhandled adjustment to Y advancement\n");
            }
            break;
        }

        case GPOS_LOOKUP_ADJUST_PAIR:
        {
            POINT advance[2]= {{0,0},{0,0}};
            POINT adjust[2]= {{0,0},{0,0}};
            double devX, devY;
            int index_offset;
            int write_dir = (analysis->fRTL && !analysis->fLogicalOrder) ? -1 : 1;
            int offset_sign = (analysis->fRTL && analysis->fLogicalOrder) ? -1 : 1;

            index_offset = GPOS_apply_PairAdjustment(look, analysis, glyphs,
                    glyph_index, glyph_count, ppem, adjust, advance);
            if (adjust[0].x || adjust[0].y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, adjust[0].x, adjust[0].y, &devX, &devY);
                pGoffset[glyph_index].du += round(devX) * offset_sign;
                pGoffset[glyph_index].dv += round(devY);
            }
            if (advance[0].x || advance[0].y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, advance[0].x, advance[0].y, &devX, &devY);
                piAdvance[glyph_index] += round(devX);
            }
            if (adjust[1].x || adjust[1].y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, adjust[1].x, adjust[1].y, &devX, &devY);
                pGoffset[glyph_index + write_dir].du += round(devX) * offset_sign;
                pGoffset[glyph_index + write_dir].dv += round(devY);
            }
            if (advance[1].x || advance[1].y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, advance[1].x, advance[1].y, &devX, &devY);
                piAdvance[glyph_index + write_dir] += round(devX);
            }
            return index_offset;
        }

        case GPOS_LOOKUP_ATTACH_CURSIVE:
        {
            POINT desU = {0,0};
            double devX, devY;
            int write_dir = (analysis->fRTL && !analysis->fLogicalOrder) ? -1 : 1;

            GPOS_apply_CursiveAttachment(look, analysis, glyphs, glyph_index, glyph_count, ppem, &desU);
            if (desU.x || desU.y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, desU.x, desU.y, &devX, &devY);
                /* Windows does not appear to apply X offsets here */
                pGoffset[glyph_index].dv = round(devY) + pGoffset[glyph_index+write_dir].dv;
            }
            break;
        }

        case GPOS_LOOKUP_ATTACH_MARK_TO_BASE:
        {
            double devX, devY;
            POINT desU = {0,0};
            int base_index = GPOS_apply_MarkToBase(script_cache, look, analysis,
                    glyphs, glyph_index, glyph_count, ppem, &desU);
            if (base_index != -1)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, desU.x, desU.y, &devX, &devY);
                if (!analysis->fRTL) pGoffset[glyph_index].du = round(devX) - piAdvance[base_index];
                else
                {
                    if (analysis->fLogicalOrder) devX *= -1;
                    pGoffset[glyph_index].du = round(devX);
                }
                pGoffset[glyph_index].dv = round(devY);
            }
            break;
        }

        case GPOS_LOOKUP_ATTACH_MARK_TO_LIGATURE:
        {
            double devX, devY;
            POINT desU = {0,0};
            GPOS_apply_MarkToLigature(look, analysis, glyphs, glyph_index, glyph_count, ppem, &desU);
            if (desU.x || desU.y)
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, desU.x, desU.y, &devX, &devY);
                pGoffset[glyph_index].du = (round(devX) - piAdvance[glyph_index-1]);
                pGoffset[glyph_index].dv = round(devY);
            }
            break;
        }

        case GPOS_LOOKUP_ATTACH_MARK_TO_MARK:
        {
            double devX, devY;
            POINT desU = {0,0};
            int write_dir = (analysis->fRTL && !analysis->fLogicalOrder) ? -1 : 1;
            if (GPOS_apply_MarkToMark(look, analysis, glyphs, glyph_index, glyph_count, ppem, &desU))
            {
                GPOS_convert_design_units_to_device(lpotm, lplogfont, desU.x, desU.y, &devX, &devY);
                if (analysis->fRTL && analysis->fLogicalOrder) devX *= -1;
                pGoffset[glyph_index].du = round(devX) + pGoffset[glyph_index - write_dir].du;
                pGoffset[glyph_index].dv = round(devY) + pGoffset[glyph_index - write_dir].dv;
            }
            break;
        }

        case GPOS_LOOKUP_POSITION_CONTEXT:
            return GPOS_apply_ContextPos(script_cache, lpotm, lplogfont, analysis, piAdvance,
                    lookup, look, glyphs, glyph_index, glyph_count, pGoffset);

        case GPOS_LOOKUP_POSITION_CONTEXT_CHAINED:
            return GPOS_apply_ChainContextPos(script_cache, lpotm, lplogfont, analysis, piAdvance,
                    lookup, look, glyphs, glyph_index, glyph_count, pGoffset);

        default:
            FIXME("Unhandled GPOS lookup type %#x.\n", type);
    }
    return 1;
}