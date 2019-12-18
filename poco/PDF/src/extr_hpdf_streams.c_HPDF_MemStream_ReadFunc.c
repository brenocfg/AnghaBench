#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; } ;
struct TYPE_7__ {int r_ptr_idx; scalar_t__ buf_siz; scalar_t__ r_pos; scalar_t__ w_pos; int /*<<< orphan*/ * r_ptr; TYPE_5__* buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_MemStreamAttr ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_List_ItemAt (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * HPDF_MemStream_GetBufPtr (TYPE_1__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_STREAM_EOF ; 

HPDF_STATUS
HPDF_MemStream_ReadFunc  (HPDF_Stream  stream,
                          HPDF_BYTE    *buf,
                          HPDF_UINT    *size)
{
    HPDF_MemStreamAttr attr = (HPDF_MemStreamAttr)stream->attr;
    HPDF_UINT buf_size;
    HPDF_UINT rlen = *size;

    HPDF_PTRACE((" HPDF_MemStream_ReadFunc\n"));

    *size = 0;

    while (rlen > 0) {
        HPDF_UINT tmp_len;

        if (attr->buf->count == 0)
            return HPDF_STREAM_EOF;

        if (attr->buf->count - 1 > attr->r_ptr_idx)
            tmp_len = attr->buf_siz - attr->r_pos;
        else if (attr->buf->count - 1 == attr->r_ptr_idx)
            tmp_len = attr->w_pos - attr->r_pos;
        else
            return HPDF_STREAM_EOF;

        if (!attr->r_ptr)
            attr->r_ptr = (HPDF_BYTE*)HPDF_List_ItemAt (attr->buf,
                            attr->r_ptr_idx);

        if (tmp_len >= rlen) {
            HPDF_MemCpy (buf, attr->r_ptr, rlen);
            attr->r_pos += rlen;
            *size += rlen;
            attr->r_ptr += rlen;
            return HPDF_OK;
        } else {
            buf = HPDF_MemCpy (buf, attr->r_ptr, tmp_len);
            rlen -= tmp_len;
            *size += tmp_len;

            if (attr->r_ptr_idx == attr->buf->count - 1) {
                attr->r_ptr += tmp_len;
                attr->r_pos += tmp_len;
                return HPDF_STREAM_EOF;
            }

            attr->r_ptr_idx++;
            attr->r_pos = 0;
            attr->r_ptr = HPDF_MemStream_GetBufPtr (stream, attr->r_ptr_idx,
                    &buf_size);
        }
    }

    return HPDF_OK;
}