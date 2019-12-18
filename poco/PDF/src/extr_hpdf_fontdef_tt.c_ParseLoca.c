#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
struct TYPE_12__ {int /*<<< orphan*/  offset; } ;
struct TYPE_10__ {int* offsets; int* flgs; } ;
struct TYPE_9__ {scalar_t__ index_to_loc_format; } ;
struct TYPE_11__ {int num_glyphs; TYPE_2__ glyph_tbl; int /*<<< orphan*/  stream; TYPE_1__ header; } ;
typedef  int HPDF_UINT32 ;
typedef  int HPDF_UINT16 ;
typedef  int HPDF_UINT ;
typedef  TYPE_3__* HPDF_TTFontDefAttr ;
typedef  TYPE_4__ HPDF_TTFTable ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_5__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 TYPE_4__* FindTable (TYPE_5__*,char*) ; 
 scalar_t__ GetUINT16 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GetUINT32 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 void* HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_Stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_TTF_MISSING_TABLE ; 

__attribute__((used)) static HPDF_STATUS
ParseLoca  (HPDF_FontDef  fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable *tbl = FindTable (fontdef, "loca");
    HPDF_STATUS ret;
    HPDF_UINT i;
    HPDF_UINT32 *poffset;

    HPDF_PTRACE ((" HPDF_TTFontDef_ParseLoca\n"));

    if (!tbl)
        return HPDF_SetError (fontdef->error, HPDF_TTF_MISSING_TABLE, 8);

    ret = HPDF_Stream_Seek (attr->stream, tbl->offset, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    /* allocate glyph-offset-table. */
    attr->glyph_tbl.offsets = HPDF_GetMem (fontdef->mmgr,
        sizeof (HPDF_UINT32) * (attr->num_glyphs + 1));

    if (!attr->glyph_tbl.offsets)
        return HPDF_Error_GetCode (fontdef->error);

    HPDF_MemSet (attr->glyph_tbl.offsets, 0,
            sizeof (HPDF_UINT32) * (attr->num_glyphs + 1));

    /* allocate glyph-flg-table.
     * this flgs are used to judge whether glyphs should be embedded.
     */
    attr->glyph_tbl.flgs = HPDF_GetMem (fontdef->mmgr,
        sizeof (HPDF_BYTE) * attr->num_glyphs);

    if (!attr->glyph_tbl.flgs)
        return HPDF_Error_GetCode (fontdef->error);

    HPDF_MemSet (attr->glyph_tbl.flgs, 0,
        sizeof (HPDF_BYTE) * attr->num_glyphs);
    attr->glyph_tbl.flgs[0] = 1;

    poffset = attr->glyph_tbl.offsets;
    if (attr->header.index_to_loc_format == 0) {
        /* short version */
        for (i = 0; i <= attr->num_glyphs; i++) {
            HPDF_UINT16 tmp = 0;

            if ((ret = GetUINT16 (attr->stream, &tmp)) != HPDF_OK)
                return ret;

            *poffset = tmp;
            poffset++;
        }
    } else {
        /* long version */
        for (i = 0; i <= attr->num_glyphs; i++) {
            if ((ret = GetUINT32 (attr->stream, poffset)) != HPDF_OK)
                return ret;

            poffset++;
        }
    }


#ifdef LIBHPDF_DEBUG
    poffset = attr->glyph_tbl.offsets;
    for (i = 0; i <= attr->num_glyphs; i++) {
        HPDF_PTRACE((" ParseLOCA offset[%u]=%u\n", i, (HPDF_UINT)*poffset));
        poffset++;
    }
#endif


    return HPDF_OK;
}