#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  error; } ;
struct TYPE_11__ {int /*<<< orphan*/  free_fn; int /*<<< orphan*/  size_fn; int /*<<< orphan*/  tell_fn; int /*<<< orphan*/  seek_fn; int /*<<< orphan*/  read_fn; int /*<<< orphan*/  write_fn; scalar_t__ buf_siz; scalar_t__ w_pos; struct TYPE_11__* attr; TYPE_3__* mmgr; int /*<<< orphan*/  error; int /*<<< orphan*/  type; int /*<<< orphan*/  sig_bytes; int /*<<< orphan*/  buf; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream_Rec ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_MemStreamAttr_Rec ;
typedef  TYPE_1__* HPDF_MemStreamAttr ;
typedef  TYPE_3__* HPDF_MMgr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_DEF_ITEMS_PER_BLOCK ; 
 int /*<<< orphan*/  HPDF_FreeMem (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ HPDF_GetMem (TYPE_3__*,int) ; 
 int /*<<< orphan*/  HPDF_List_New (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_MemStream_FreeFunc ; 
 int /*<<< orphan*/  HPDF_MemStream_ReadFunc ; 
 int /*<<< orphan*/  HPDF_MemStream_SeekFunc ; 
 int /*<<< orphan*/  HPDF_MemStream_SizeFunc ; 
 int /*<<< orphan*/  HPDF_MemStream_TellFunc ; 
 int /*<<< orphan*/  HPDF_MemStream_WriteFunc ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_STREAM_BUF_SIZ ; 
 int /*<<< orphan*/  HPDF_STREAM_MEMORY ; 
 int /*<<< orphan*/  HPDF_STREAM_SIG_BYTES ; 

HPDF_Stream
HPDF_MemStream_New  (HPDF_MMgr  mmgr,
                     HPDF_UINT  buf_siz)
{
    HPDF_Stream stream;

    HPDF_PTRACE((" HPDF_MemStream_New\n"));

    /* Create new HPDF_Stream object. */
    stream = (HPDF_Stream)HPDF_GetMem (mmgr, sizeof(HPDF_Stream_Rec));

    if (stream) {
        /* Create attribute struct. */
        HPDF_MemStreamAttr attr = (HPDF_MemStreamAttr)HPDF_GetMem (mmgr,
                sizeof(HPDF_MemStreamAttr_Rec));

        if (!attr) {
            HPDF_FreeMem (mmgr, stream);
            return NULL;
        }

        HPDF_MemSet (stream, 0, sizeof(HPDF_Stream_Rec));
        HPDF_MemSet (attr, 0, sizeof(HPDF_MemStreamAttr_Rec));

        attr->buf = HPDF_List_New (mmgr, HPDF_DEF_ITEMS_PER_BLOCK);
        if (!attr->buf) {
            HPDF_FreeMem (mmgr, stream);
            HPDF_FreeMem (mmgr, attr);
            return NULL;
        }

        stream->sig_bytes = HPDF_STREAM_SIG_BYTES;
        stream->type = HPDF_STREAM_MEMORY;
        stream->error = mmgr->error;
        stream->mmgr = mmgr;
        stream->attr = attr;
        attr->buf_siz = (buf_siz > 0) ? buf_siz : HPDF_STREAM_BUF_SIZ;
        attr->w_pos = attr->buf_siz;

        stream->write_fn = HPDF_MemStream_WriteFunc;
        stream->read_fn = HPDF_MemStream_ReadFunc;
        stream->seek_fn = HPDF_MemStream_SeekFunc;
        stream->tell_fn = HPDF_MemStream_TellFunc;
        stream->size_fn = HPDF_MemStream_SizeFunc;
        stream->free_fn = HPDF_MemStream_FreeFunc;
    }

    return stream;
}