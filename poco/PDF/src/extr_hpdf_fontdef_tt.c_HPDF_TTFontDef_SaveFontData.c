#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_32__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  error; int /*<<< orphan*/  attr; } ;
struct TYPE_31__ {int size; } ;
struct TYPE_30__ {int length; int offset; int check_sum; scalar_t__ tag; } ;
struct TYPE_28__ {scalar_t__ index_to_loc_format; } ;
struct TYPE_27__ {int sfnt_version; int search_range; int entry_selector; int range_shift; } ;
struct TYPE_29__ {int num_glyphs; int length1; TYPE_5__* stream; TYPE_2__ header; TYPE_1__ offset_tbl; } ;
typedef  int HPDF_UINT32 ;
typedef  int HPDF_UINT16 ;
typedef  int HPDF_UINT ;
typedef  TYPE_3__* HPDF_TTFontDefAttr ;
typedef  TYPE_4__ HPDF_TTFTable ;
typedef  TYPE_5__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_6__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 TYPE_4__* FindTable (TYPE_6__*,scalar_t__) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int*) ; 
 int* HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_MemCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* HPDF_MemStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_MemStream_Rewrite (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int HPDF_REQUIRED_TAGS_COUNT ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 int /*<<< orphan*/  HPDF_STREAM_BUF_SIZ ; 
 scalar_t__ HPDF_STREAM_EOF ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_Stream_Free (TYPE_5__*) ; 
 scalar_t__ HPDF_Stream_Read (TYPE_5__*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ HPDF_Stream_Seek (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Write (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HPDF_Stream_WriteToStream (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_TTF_MISSING_TABLE ; 
 scalar_t__* REQUIRED_TAGS ; 
 scalar_t__ RecreateGLYF (TYPE_6__*,int*,TYPE_5__*) ; 
 scalar_t__ RecreateName (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  UINT32Swap (int*) ; 
 scalar_t__ WriteHeader (TYPE_6__*,TYPE_5__*,int*) ; 
 scalar_t__ WriteUINT16 (TYPE_5__*,int) ; 
 scalar_t__ WriteUINT32 (TYPE_5__*,int) ; 

HPDF_STATUS
HPDF_TTFontDef_SaveFontData  (HPDF_FontDef   fontdef,
                              HPDF_Stream    stream)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable tmp_tbl[HPDF_REQUIRED_TAGS_COUNT];
    HPDF_Stream tmp_stream;
    HPDF_UINT32 *new_offsets;
    HPDF_UINT i;
    HPDF_UINT32 check_sum_ptr = 0;
    HPDF_STATUS ret;
    HPDF_UINT32 offset_base;
    HPDF_UINT32 tmp_check_sum = 0xB1B0AFBA;
    HPDF_TTFTable emptyTable;
    emptyTable.length = 0;
    emptyTable.offset = 0;

    HPDF_PTRACE ((" SaveFontData\n"));

    ret = WriteUINT32 (stream, attr->offset_tbl.sfnt_version);
    ret += WriteUINT16 (stream, HPDF_REQUIRED_TAGS_COUNT);
    ret += WriteUINT16 (stream, attr->offset_tbl.search_range);
    ret += WriteUINT16 (stream, attr->offset_tbl.entry_selector);
    ret += WriteUINT16 (stream, attr->offset_tbl.range_shift);

    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (fontdef->error);

    tmp_stream = HPDF_MemStream_New (fontdef->mmgr, HPDF_STREAM_BUF_SIZ);
    if (!tmp_stream)
        return HPDF_Error_GetCode (fontdef->error);

    offset_base = 12 + 16 * HPDF_REQUIRED_TAGS_COUNT;

    new_offsets = HPDF_GetMem (fontdef->mmgr,
            sizeof (HPDF_UINT32) * (attr->num_glyphs + 1));
    if (!new_offsets) {
        HPDF_Stream_Free (tmp_stream);
        return HPDF_Error_GetCode (fontdef->error);
    }

    for (i = 0; i < HPDF_REQUIRED_TAGS_COUNT; i++) {
        HPDF_TTFTable *tbl = FindTable (fontdef, REQUIRED_TAGS[i]);
        HPDF_UINT32 length;
        HPDF_UINT new_offset;
        HPDF_UINT32 *poffset;
        HPDF_UINT32 value;

	if (!tbl) {
	    tbl = &emptyTable;
	    HPDF_MemCpy((HPDF_BYTE *)tbl->tag,
			(const HPDF_BYTE *)REQUIRED_TAGS[i], 4);
	}

        if (!tbl) {
            ret = HPDF_SetError (fontdef->error, HPDF_TTF_MISSING_TABLE, i);
            goto Exit;
        }

        ret = HPDF_Stream_Seek (attr->stream, tbl->offset, HPDF_SEEK_SET);
        if (ret != HPDF_OK)
            goto Exit;

        length = tbl->length;
        new_offset = tmp_stream->size;

        if (HPDF_MemCmp ((HPDF_BYTE *)tbl->tag, (HPDF_BYTE *)"head", 4) == 0) {
            ret = WriteHeader (fontdef, tmp_stream, &check_sum_ptr);
        } else if (HPDF_MemCmp ((HPDF_BYTE *)tbl->tag, (HPDF_BYTE *)"glyf", 4) == 0) {
            ret = RecreateGLYF (fontdef, new_offsets, tmp_stream);
        } else if (HPDF_MemCmp ((HPDF_BYTE *)tbl->tag, (HPDF_BYTE *)"loca", 4) == 0) {
            HPDF_UINT j;

            HPDF_MemSet (&value, 0, 4);
            poffset = new_offsets;

            if (attr->header.index_to_loc_format == 0) {
                for (j = 0; j <= attr->num_glyphs; j++) {
                    ret += WriteUINT16 (tmp_stream, (HPDF_UINT16)*poffset);
                    poffset++;
                }
            } else {
                for (j = 0; j <= attr->num_glyphs; j++) {
                    ret += WriteUINT32 (tmp_stream, *poffset);
                    poffset++;
                }
            }
        } else if (HPDF_MemCmp ((HPDF_BYTE *)tbl->tag, (HPDF_BYTE *)"name", 4) == 0) {
            ret = RecreateName (fontdef, tmp_stream);
        } else {
            HPDF_UINT size = 4;

            while (length > 4) {
                value = 0;
                size = 4;
                ret = HPDF_Stream_Read (attr->stream, (HPDF_BYTE *)&value, &size);
                ret += HPDF_Stream_Write (tmp_stream, (HPDF_BYTE *)&value, size);
                length -= 4;
            }

            value = 0;
            size = length;
            ret += HPDF_Stream_Read (attr->stream, (HPDF_BYTE *)&value, &size);
            ret += HPDF_Stream_Write (tmp_stream, (HPDF_BYTE *)&value, size);
        }

        tmp_tbl[i].offset = new_offset;
        tmp_tbl[i].length = tmp_stream->size - new_offset;

        if (ret != HPDF_OK)
            goto Exit;
    }

    /* recalcurate checksum */
    for (i = 0; i < HPDF_REQUIRED_TAGS_COUNT; i++) {
        HPDF_TTFTable tbl = tmp_tbl[i];
        HPDF_UINT32 buf;
        HPDF_UINT length = tbl.length;

        HPDF_PTRACE((" SaveFontData() tag[%s] length=%u\n",
                REQUIRED_TAGS[i], length));

        if ((ret = HPDF_Stream_Seek (tmp_stream, tbl.offset, HPDF_SEEK_SET))
                != HPDF_OK)
            break;

        tbl.check_sum = 0;
        while (length > 0) {
            HPDF_UINT rlen = (length > 4) ? 4 : length;
            buf = 0;
            if ((ret = HPDF_Stream_Read (tmp_stream, (HPDF_BYTE *)&buf, &rlen))
                    != HPDF_OK)
                break;

            UINT32Swap (&buf);
            tbl.check_sum += buf;
            length -= rlen;
        }

        if (ret != HPDF_OK)
            break;

        HPDF_PTRACE((" SaveFontData tag[%s] check-sum=%u offset=%u\n",
                    REQUIRED_TAGS[i], (HPDF_UINT)tbl.check_sum,
                    (HPDF_UINT)tbl.offset));

        ret += HPDF_Stream_Write (stream, (HPDF_BYTE *)REQUIRED_TAGS[i], 4);
        ret += WriteUINT32 (stream, tbl.check_sum);
        tbl.offset += offset_base;
        ret += WriteUINT32 (stream, tbl.offset);
        ret += WriteUINT32 (stream, tbl.length);

        if (ret != HPDF_OK)
            break;
    }

    if (ret != HPDF_OK)
        goto Exit;

    /* calucurate checkSumAdjustment.*/
    ret = HPDF_Stream_Seek (tmp_stream, 0, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        goto Exit;

    for (;;) {
        HPDF_UINT32 buf;
        HPDF_UINT siz = sizeof(buf);

        ret = HPDF_Stream_Read (tmp_stream, (HPDF_BYTE *)&buf, &siz);
        if (ret != HPDF_OK || siz <= 0) {
            if (ret == HPDF_STREAM_EOF)
                ret = HPDF_OK;
            break;
        }

        UINT32Swap (&buf);
        tmp_check_sum -= buf;
    }

    if (ret != HPDF_OK)
        goto Exit;

    HPDF_PTRACE((" SaveFontData new checkSumAdjustment=%u\n",
                (HPDF_UINT)tmp_check_sum));

    UINT32Swap (&tmp_check_sum);

    ret = HPDF_Stream_Seek (tmp_stream, check_sum_ptr, HPDF_SEEK_SET);
    if (ret == HPDF_OK) {
        ret = HPDF_MemStream_Rewrite (tmp_stream, (HPDF_BYTE *)&tmp_check_sum,
            4);
    }

    if (ret != HPDF_OK)
        goto Exit;

    attr->length1 = tmp_stream->size + offset_base;
    ret = HPDF_Stream_WriteToStream (tmp_stream, stream, 0, NULL);

    goto Exit;

Exit:
    HPDF_FreeMem (fontdef->mmgr, new_offsets);
    HPDF_Stream_Free (tmp_stream);
    return ret;
}