#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ buf_siz; scalar_t__ w_pos; int /*<<< orphan*/ * w_ptr; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_MemStreamAttr ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HPDF_List_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_MemStream_InWrite  (HPDF_Stream      stream,
                         const HPDF_BYTE  **ptr,
                         HPDF_UINT        *count)
{
    HPDF_MemStreamAttr attr = (HPDF_MemStreamAttr)stream->attr;
    HPDF_UINT rsize = attr->buf_siz - attr->w_pos;

    HPDF_PTRACE((" HPDF_MemStream_InWrite\n"));

    if (*count <= 0)
        return HPDF_OK;

    if (rsize >= *count) {
        HPDF_MemCpy (attr->w_ptr, *ptr, *count);
        attr->w_ptr += *count;
        attr->w_pos += *count;
        *count = 0;
    } else {
        if (rsize > 0) {
            HPDF_MemCpy (attr->w_ptr, *ptr, rsize);
            *ptr += rsize;
            *count -= rsize;
        }
        attr->w_ptr = (HPDF_BYTE*)HPDF_GetMem (stream->mmgr, attr->buf_siz);

        if (attr->w_ptr == NULL)
           return HPDF_Error_GetCode (stream->error);

        if (HPDF_List_Add (attr->buf, attr->w_ptr) != HPDF_OK) {
            HPDF_FreeMem (stream->mmgr, attr->w_ptr);
            attr->w_ptr = NULL;

            return HPDF_Error_GetCode (stream->error);
        }
        attr->w_pos = 0;
    }
    return HPDF_OK;
}