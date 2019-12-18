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
struct TYPE_13__ {int /*<<< orphan*/  missing_width; int /*<<< orphan*/  attr; } ;
struct TYPE_12__ {scalar_t__ advance_width; } ;
struct TYPE_10__ {int units_per_em; } ;
struct TYPE_9__ {int* flgs; } ;
struct TYPE_11__ {size_t num_glyphs; TYPE_2__ header; scalar_t__ embedding; TYPE_1__ glyph_tbl; TYPE_4__* h_metric; } ;
typedef  size_t HPDF_UINT16 ;
typedef  int HPDF_UINT ;
typedef  TYPE_3__* HPDF_TTFontDefAttr ;
typedef  TYPE_4__ HPDF_TTF_LongHorMetric ;
typedef  int /*<<< orphan*/  HPDF_INT16 ;
typedef  TYPE_5__* HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  CheckCompositGryph (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 size_t HPDF_TTFontDef_GetGlyphid (TYPE_5__*,size_t) ; 

HPDF_INT16
HPDF_TTFontDef_GetCharWidth  (HPDF_FontDef   fontdef,
                              HPDF_UINT16    unicode)
{
    HPDF_UINT16 advance_width;
    HPDF_TTF_LongHorMetric hmetrics;
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_UINT16 gid = HPDF_TTFontDef_GetGlyphid (fontdef, unicode);

    HPDF_PTRACE((" HPDF_TTFontDef_GetCharWidth\n"));

    if (gid >= attr->num_glyphs) {
        HPDF_PTRACE((" HPDF_TTFontDef_GetCharWidth WARNING gid > "
                    "num_glyphs %u > %u\n", gid, attr->num_glyphs));
        return fontdef->missing_width;
    }

    hmetrics = attr->h_metric[gid];

    if (!attr->glyph_tbl.flgs[gid]) {
        attr->glyph_tbl.flgs[gid] = 1;

        if (attr->embedding)
            CheckCompositGryph (fontdef, gid);
    }

    advance_width = (HPDF_UINT16)((HPDF_UINT)hmetrics.advance_width * 1000 /
            attr->header.units_per_em);

    return (HPDF_INT16)advance_width;
}