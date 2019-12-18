#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
struct TYPE_11__ {scalar_t__ offsets; scalar_t__ flgs; } ;
struct TYPE_10__ {scalar_t__ table; } ;
struct TYPE_9__ {scalar_t__ glyph_id_array; scalar_t__ id_range_offset; scalar_t__ id_delta; scalar_t__ start_count; scalar_t__ end_count; } ;
struct TYPE_8__ {scalar_t__ name_records; } ;
struct TYPE_12__ {scalar_t__ stream; TYPE_4__ glyph_tbl; TYPE_3__ offset_tbl; TYPE_2__ cmap; TYPE_1__ name_tbl; scalar_t__ h_metric; scalar_t__ char_set; } ;
typedef  TYPE_5__* HPDF_TTFontDefAttr ;
typedef  TYPE_6__* HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_Stream_Free (scalar_t__) ; 

__attribute__((used)) static void
InitAttr (HPDF_FontDef  fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;

    if (attr) {
        if (attr->char_set)
            HPDF_FreeMem (fontdef->mmgr, attr->char_set);

        if (attr->h_metric)
            HPDF_FreeMem (fontdef->mmgr, attr->h_metric);

        if (attr->name_tbl.name_records)
            HPDF_FreeMem (fontdef->mmgr, attr->name_tbl.name_records);

        if (attr->cmap.end_count)
            HPDF_FreeMem (fontdef->mmgr, attr->cmap.end_count);

        if (attr->cmap.start_count)
            HPDF_FreeMem (fontdef->mmgr, attr->cmap.start_count);

        if (attr->cmap.id_delta)
            HPDF_FreeMem (fontdef->mmgr, attr->cmap.id_delta);

        if (attr->cmap.id_range_offset)
            HPDF_FreeMem (fontdef->mmgr, attr->cmap.id_range_offset);

        if (attr->cmap.glyph_id_array)
            HPDF_FreeMem (fontdef->mmgr, attr->cmap.glyph_id_array);

        if (attr->offset_tbl.table)
            HPDF_FreeMem (fontdef->mmgr, attr->offset_tbl.table);

        if (attr->glyph_tbl.flgs)
            HPDF_FreeMem (fontdef->mmgr, attr->glyph_tbl.flgs);

        if (attr->glyph_tbl.offsets)
            HPDF_FreeMem (fontdef->mmgr, attr->glyph_tbl.offsets);

        if (attr->stream)
            HPDF_Stream_Free (attr->stream);
    }
}