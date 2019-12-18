#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ r_ptr_idx; scalar_t__ r_pos; scalar_t__ w_pos; scalar_t__ buf_siz; int /*<<< orphan*/  r_ptr; TYPE_1__* buf; int /*<<< orphan*/  w_ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {scalar_t__ count; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_2__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_3__* HPDF_MemStreamAttr ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_MemStream_GetBufPtr (TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  HPDF_MemStream_WriteFunc (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_MemStream_Rewrite  (HPDF_Stream  stream,
                         HPDF_BYTE    *buf,
                         HPDF_UINT    size)
{
    HPDF_MemStreamAttr attr = (HPDF_MemStreamAttr)stream->attr;
    HPDF_UINT buf_size;
    HPDF_UINT rlen = size;

    HPDF_PTRACE((" HPDF_MemStream_Rewrite\n"));

    while (rlen > 0) {
        HPDF_UINT tmp_len;

        if (attr->buf->count <= attr->r_ptr_idx) {
            HPDF_STATUS ret = HPDF_MemStream_WriteFunc (stream, buf, rlen);
            attr->r_ptr_idx = attr->buf->count;
            attr->r_pos = attr->w_pos;
            attr->r_ptr = attr->w_ptr;
            return ret;
        } else if (attr->buf->count == attr->r_ptr_idx)
            tmp_len = attr->w_pos - attr->r_pos;
        else
            tmp_len = attr->buf_siz - attr->r_pos;

        if (tmp_len >= rlen) {
            HPDF_MemCpy(attr->r_ptr, buf, rlen);
            attr->r_pos += rlen;
            attr->r_ptr += rlen;
            return HPDF_OK;
        } else {
            HPDF_MemCpy(attr->r_ptr, buf, tmp_len);
            buf += tmp_len;
            rlen -= tmp_len;
            attr->r_ptr_idx++;

            if (attr->buf->count > attr->r_ptr_idx) {
                attr->r_pos = 0;
                attr->r_ptr = HPDF_MemStream_GetBufPtr (stream, attr->r_ptr_idx,
                        &buf_size);
            }
        }
    }
    return HPDF_OK;
}