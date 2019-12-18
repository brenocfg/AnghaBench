#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* top; void* right; void* bottom; void* left; } ;
struct TYPE_13__ {int /*<<< orphan*/  attr; } ;
struct TYPE_11__ {scalar_t__ index_to_loc_format; int units_per_em; } ;
struct TYPE_10__ {int* offsets; scalar_t__ base_offset; } ;
struct TYPE_12__ {TYPE_2__ header; int /*<<< orphan*/  stream; TYPE_1__ glyph_tbl; } ;
typedef  size_t HPDF_UINT16 ;
typedef  TYPE_3__* HPDF_TTFontDefAttr ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  void* HPDF_REAL ;
typedef  int HPDF_INT32 ;
typedef  scalar_t__ HPDF_INT16 ;
typedef  int HPDF_INT ;
typedef  TYPE_4__* HPDF_FontDef ;
typedef  TYPE_5__ HPDF_Box ;

/* Variables and functions */
 scalar_t__ GetINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 scalar_t__ HPDF_Stream_Seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t HPDF_TTFontDef_GetGlyphid (TYPE_4__*,size_t) ; 
 TYPE_5__ HPDF_ToBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_Box
HPDF_TTFontDef_GetCharBBox  (HPDF_FontDef   fontdef,
                             HPDF_UINT16    unicode)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_UINT16 gid = HPDF_TTFontDef_GetGlyphid(fontdef, unicode);
    HPDF_STATUS ret;
    HPDF_Box bbox = HPDF_ToBox(0, 0, 0, 0);
    HPDF_INT16 i;
    HPDF_INT m;

    if (gid == 0) {
        HPDF_PTRACE ((" GetCharHeight cannot get gid char=0x%04x\n", unicode));
        return bbox;
    }

    if (attr->header.index_to_loc_format == 0)
        m = 2;
    else
        m = 1;

    ret = HPDF_Stream_Seek (attr->stream, attr->glyph_tbl.base_offset +
                     attr->glyph_tbl.offsets[gid] * m + 2, HPDF_SEEK_SET);

    if (ret != HPDF_OK)
        return bbox;

    ret += GetINT16 (attr->stream, &i);
    bbox.left = (HPDF_REAL)((HPDF_INT32)i * 1000 / attr->header.units_per_em);

    ret += GetINT16 (attr->stream, &i);
    bbox.bottom = (HPDF_REAL)((HPDF_INT32)i * 1000 / attr->header.units_per_em);

    ret += GetINT16 (attr->stream, &i);
    bbox.right = (HPDF_REAL)((HPDF_INT32)i * 1000 / attr->header.units_per_em);

    ret += GetINT16 (attr->stream, &i);
    bbox.top = (HPDF_REAL)((HPDF_INT32)i * 1000 / attr->header.units_per_em);

    if (ret != HPDF_OK)
        return HPDF_ToBox(0, 0, 0, 0);

    HPDF_PTRACE((" PdfTTFontDef_GetCharBBox char=0x%04X, "
            "box=[%f,%f,%f,%f]\n", unicode, bbox.left, bbox.bottom, bbox.right,
            bbox.top));

    return bbox;
}