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
struct TYPE_13__ {int /*<<< orphan*/  attr; } ;
struct TYPE_12__ {int size; } ;
struct TYPE_10__ {scalar_t__ index_to_loc_format; } ;
struct TYPE_9__ {int* flgs; int* offsets; scalar_t__ base_offset; } ;
struct TYPE_11__ {size_t num_glyphs; TYPE_2__ header; int /*<<< orphan*/  stream; TYPE_1__ glyph_tbl; } ;
typedef  int HPDF_UINT32 ;
typedef  int HPDF_UINT ;
typedef  TYPE_3__* HPDF_TTFontDefAttr ;
typedef  TYPE_4__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  size_t HPDF_INT ;
typedef  TYPE_5__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 int HPDF_STREAM_BUF_SIZ ; 
 int /*<<< orphan*/  HPDF_Stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  HPDF_Stream_Seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Stream_Write (TYPE_4__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HPDF_STATUS
RecreateGLYF  (HPDF_FontDef   fontdef,
               HPDF_UINT32   *new_offsets,
               HPDF_Stream    stream)
{
    HPDF_UINT32 save_offset = 0;
    HPDF_UINT32 start_offset = stream->size;
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_STATUS ret;
    HPDF_INT i;

    HPDF_PTRACE ((" RecreateGLYF\n"));

    for (i = 0; i < attr->num_glyphs; i++) {
        HPDF_BYTE buf[HPDF_STREAM_BUF_SIZ];

        if (attr->glyph_tbl.flgs[i] == 1) {
            HPDF_UINT offset = attr->glyph_tbl.offsets[i];
            HPDF_UINT len = attr->glyph_tbl.offsets[i + 1] - offset;

            new_offsets[i] = stream->size - start_offset;
            if (attr->header.index_to_loc_format == 0) {
                new_offsets[i] /= 2;
                len *= 2;
            }

            HPDF_PTRACE((" RecreateGLYF[%u] move from [%u] to [%u]\n", i,
                        (HPDF_UINT)attr->glyph_tbl.base_offset + offset,
                        (HPDF_UINT)new_offsets[i]));

            if (attr->header.index_to_loc_format == 0)
                offset *= 2;

            offset += attr->glyph_tbl.base_offset;

            if ((ret = HPDF_Stream_Seek (attr->stream, offset, HPDF_SEEK_SET))
                    != HPDF_OK)
                return ret;

            while (len > 0) {
                HPDF_UINT tmp_len =
                    (len > HPDF_STREAM_BUF_SIZ) ? HPDF_STREAM_BUF_SIZ : len;

                HPDF_MemSet (buf, 0, tmp_len);

                if ((ret = HPDF_Stream_Read (attr->stream, buf, &tmp_len))
                        != HPDF_OK)
                    return ret;

                if ((ret = HPDF_Stream_Write (stream, buf, tmp_len)) !=
                        HPDF_OK)
                    return ret;

                len -= tmp_len;
            }

            save_offset = stream->size - start_offset;
            if (attr->header.index_to_loc_format == 0)
                save_offset /= 2;
        } else {
            new_offsets[i] = save_offset;
        }
    }

    new_offsets[attr->num_glyphs] = save_offset;

#ifdef DEBUG
    for (i = 0; i <= attr->num_glyphs; i++) {
        HPDF_PTRACE((" RecreateGLYF[%u] offset=%u\n", i, new_offsets[i]));
    }
#endif

    return HPDF_OK;
}