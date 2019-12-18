#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {int* offsets; int* flgs; scalar_t__ base_offset; } ;
struct TYPE_6__ {scalar_t__ index_to_loc_format; } ;
struct TYPE_8__ {int num_glyphs; TYPE_2__ glyph_tbl; int /*<<< orphan*/  stream; TYPE_1__ header; } ;
typedef  size_t HPDF_UINT16 ;
typedef  int HPDF_UINT ;
typedef  TYPE_3__* HPDF_TTFontDefAttr ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int HPDF_INT16 ;
typedef  TYPE_4__* HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  GetINT16 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_CUR ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 int /*<<< orphan*/  HPDF_Stream_Seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_STATUS
CheckCompositGryph  (HPDF_FontDef   fontdef,
                     HPDF_UINT16    gid)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_UINT offset = attr->glyph_tbl.offsets[gid];
    /* HPDF_UINT len = attr->glyph_tbl.offsets[gid + 1] - offset; */
    HPDF_STATUS ret;

    HPDF_PTRACE ((" CheckCompositGryph\n"));

    if (attr->header.index_to_loc_format == 0)
        offset *= 2;

    offset += attr->glyph_tbl.base_offset;

    if ((ret = HPDF_Stream_Seek (attr->stream, offset, HPDF_SEEK_SET))
            != HPDF_OK) {
        return ret;
    } else {
        HPDF_INT16 num_of_contours;
        HPDF_INT16 flags;
        HPDF_INT16 glyph_index;
        const HPDF_UINT16 ARG_1_AND_2_ARE_WORDS = 1;
        const HPDF_UINT16 WE_HAVE_A_SCALE  = 8;
        const HPDF_UINT16 MORE_COMPONENTS = 32;
        const HPDF_UINT16 WE_HAVE_AN_X_AND_Y_SCALE = 64;
        const HPDF_UINT16 WE_HAVE_A_TWO_BY_TWO = 128;

        if ((ret = GetINT16 (attr->stream, &num_of_contours)) != HPDF_OK)
            return ret;

        if (num_of_contours != -1)
            return HPDF_OK;

        HPDF_PTRACE ((" CheckCompositGryph composit font gid=%u\n", gid));

        if ((ret = HPDF_Stream_Seek (attr->stream, 8, HPDF_SEEK_CUR))
            != HPDF_OK)
            return ret;

        do {
            if ((ret = GetINT16 (attr->stream, &flags)) != HPDF_OK)
                return ret;

            if ((ret = GetINT16 (attr->stream, &glyph_index)) != HPDF_OK)
                return ret;

            if (flags & ARG_1_AND_2_ARE_WORDS) {
                if ((ret = HPDF_Stream_Seek (attr->stream, 4, HPDF_SEEK_CUR))
                    != HPDF_OK)
                    return ret;
            } else {
                if ((ret = HPDF_Stream_Seek (attr->stream, 2, HPDF_SEEK_CUR))
                    != HPDF_OK)
                    return ret;
            }

            if (flags & WE_HAVE_A_SCALE) {
                if ((ret = HPDF_Stream_Seek (attr->stream, 2, HPDF_SEEK_CUR))
                    != HPDF_OK)
                    return ret;
            } else if (flags & WE_HAVE_AN_X_AND_Y_SCALE) {
                if ((ret = HPDF_Stream_Seek (attr->stream, 4, HPDF_SEEK_CUR))
                    != HPDF_OK)
                    return ret;
            } else if (flags & WE_HAVE_A_TWO_BY_TWO) {
                if ((ret = HPDF_Stream_Seek (attr->stream, 8, HPDF_SEEK_CUR))
                    != HPDF_OK)
                    return ret;
            }

            if (glyph_index > 0 && glyph_index < attr->num_glyphs)
                attr->glyph_tbl.flgs[glyph_index] = 1;

            HPDF_PTRACE ((" gid=%d, num_of_contours=%d, flags=%d, "
                    "glyph_index=%d\n", gid, num_of_contours, flags,
                    glyph_index));

        } while (flags & MORE_COMPONENTS);
    }

    return HPDF_OK;
}