#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  enum gsub_lookup_type { ____Placeholder_gsub_lookup_type } gsub_lookup_type ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_15__ {int /*<<< orphan*/  SubstFormat; int /*<<< orphan*/  ExtensionLookupType; } ;
struct TYPE_14__ {int /*<<< orphan*/ * Lookup; } ;
struct TYPE_13__ {int /*<<< orphan*/ * SubTable; int /*<<< orphan*/  SubTableCount; int /*<<< orphan*/  LookupFlag; int /*<<< orphan*/  LookupType; } ;
typedef  TYPE_1__ OT_LookupTable ;
typedef  TYPE_2__ OT_LookupList ;
typedef  size_t INT ;
typedef  TYPE_3__ GSUB_ExtensionPosFormat1 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 size_t GSUB_E_NOGLYPH ; 
#define  GSUB_LOOKUP_ALTERNATE 134 
#define  GSUB_LOOKUP_CONTEXT 133 
#define  GSUB_LOOKUP_CONTEXT_CHAINED 132 
#define  GSUB_LOOKUP_EXTENSION 131 
#define  GSUB_LOOKUP_LIGATURE 130 
#define  GSUB_LOOKUP_MULTIPLE 129 
#define  GSUB_LOOKUP_SINGLE 128 
 size_t GSUB_apply_AlternateSubst (TYPE_1__ const*,int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 
 size_t GSUB_apply_ChainContextSubst (TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 
 size_t GSUB_apply_ContextSubst (TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 
 size_t GSUB_apply_LigatureSubst (TYPE_1__ const*,int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 
 size_t GSUB_apply_MultipleSubst (TYPE_1__ const*,int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 
 size_t GSUB_apply_SingleSubst (TYPE_1__ const*,int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static INT GSUB_apply_lookup(const OT_LookupList* lookup, INT lookup_index, WORD *glyphs, INT glyph_index, INT write_dir, INT *glyph_count)
{
    int offset;
    enum gsub_lookup_type type;
    const OT_LookupTable *look;

    offset = GET_BE_WORD(lookup->Lookup[lookup_index]);
    look = (const OT_LookupTable*)((const BYTE*)lookup + offset);
    type = GET_BE_WORD(look->LookupType);
    TRACE("type %#x, flag %#x, subtables %u.\n", type,
            GET_BE_WORD(look->LookupFlag),GET_BE_WORD(look->SubTableCount));

    if (type == GSUB_LOOKUP_EXTENSION)
    {
        if (GET_BE_WORD(look->SubTableCount))
        {
            const GSUB_ExtensionPosFormat1 *ext = (const GSUB_ExtensionPosFormat1 *)((const BYTE *)look + GET_BE_WORD(look->SubTable[0]));
            if (GET_BE_WORD(ext->SubstFormat) == 1)
            {
                type = GET_BE_WORD(ext->ExtensionLookupType);
                TRACE("extension type %i\n",type);
            }
            else
            {
                FIXME("Unhandled Extension Substitution Format %i\n",GET_BE_WORD(ext->SubstFormat));
            }
        }
        else
        {
            WARN("lookup type is Extension Substitution but no extension subtable exists\n");
        }
    }
    switch(type)
    {
        case GSUB_LOOKUP_SINGLE:
            return GSUB_apply_SingleSubst(look, glyphs, glyph_index, write_dir, glyph_count);
        case GSUB_LOOKUP_MULTIPLE:
            return GSUB_apply_MultipleSubst(look, glyphs, glyph_index, write_dir, glyph_count);
        case GSUB_LOOKUP_ALTERNATE:
            return GSUB_apply_AlternateSubst(look, glyphs, glyph_index, write_dir, glyph_count);
        case GSUB_LOOKUP_LIGATURE:
            return GSUB_apply_LigatureSubst(look, glyphs, glyph_index, write_dir, glyph_count);
        case GSUB_LOOKUP_CONTEXT:
            return GSUB_apply_ContextSubst(lookup, look, glyphs, glyph_index, write_dir, glyph_count);
        case GSUB_LOOKUP_CONTEXT_CHAINED:
            return GSUB_apply_ChainContextSubst(lookup, look, glyphs, glyph_index, write_dir, glyph_count);
        case GSUB_LOOKUP_EXTENSION:
            FIXME("Extension Substitution types not valid here\n");
            break;
        default:
            FIXME("Unhandled GSUB lookup type %#x.\n", type);
    }
    return GSUB_E_NOGLYPH;
}