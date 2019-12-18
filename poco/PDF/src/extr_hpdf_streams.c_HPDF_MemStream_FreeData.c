#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ count; } ;
struct TYPE_7__ {scalar_t__ r_pos; scalar_t__ r_ptr_idx; int /*<<< orphan*/ * w_ptr; int /*<<< orphan*/  buf_siz; int /*<<< orphan*/  w_pos; TYPE_4__* buf; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ size; int /*<<< orphan*/  mmgr; scalar_t__ attr; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  TYPE_2__* HPDF_MemStreamAttr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_List_Clear (TYPE_4__*) ; 
 int /*<<< orphan*/  HPDF_List_ItemAt (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_STREAM_MEMORY ; 

void
HPDF_MemStream_FreeData  (HPDF_Stream  stream)
{
    HPDF_MemStreamAttr attr;
    HPDF_UINT i;

    HPDF_PTRACE((" HPDF_MemStream_FreeData\n"));

    if (!stream || stream->type != HPDF_STREAM_MEMORY)
        return;

    attr = (HPDF_MemStreamAttr)stream->attr;

    for (i = 0; i < attr->buf->count; i++)
        HPDF_FreeMem (stream->mmgr, HPDF_List_ItemAt (attr->buf, i));

    HPDF_List_Clear(attr->buf);

    stream->size = 0;
    attr->w_pos = attr->buf_siz;
    attr->w_ptr = NULL;
    attr->r_ptr_idx = 0;
    attr->r_pos = 0;
}