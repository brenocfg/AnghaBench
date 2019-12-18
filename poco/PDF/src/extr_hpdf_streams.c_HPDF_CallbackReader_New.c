#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  error; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; void* attr; int /*<<< orphan*/  size_fn; int /*<<< orphan*/  tell_fn; int /*<<< orphan*/  seek_fn; int /*<<< orphan*/  read_fn; TYPE_2__* mmgr; int /*<<< orphan*/  error; int /*<<< orphan*/  sig_bytes; } ;
typedef  int /*<<< orphan*/  HPDF_Stream_Tell_Func ;
typedef  int /*<<< orphan*/  HPDF_Stream_Size_Func ;
typedef  int /*<<< orphan*/  HPDF_Stream_Seek_Func ;
typedef  int /*<<< orphan*/  HPDF_Stream_Rec ;
typedef  int /*<<< orphan*/  HPDF_Stream_Read_Func ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  TYPE_2__* HPDF_MMgr ;

/* Variables and functions */
 scalar_t__ HPDF_GetMem (TYPE_2__*,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_STREAM_CALLBACK ; 
 int /*<<< orphan*/  HPDF_STREAM_SIG_BYTES ; 

HPDF_Stream
HPDF_CallbackReader_New  (HPDF_MMgr              mmgr,
                          HPDF_Stream_Read_Func  read_fn,
                          HPDF_Stream_Seek_Func  seek_fn,
                          HPDF_Stream_Tell_Func  tell_fn,
                          HPDF_Stream_Size_Func  size_fn,
                          void*                  data)
{
    HPDF_Stream stream;

    HPDF_PTRACE((" HPDF_CallbackReader_New\n"));

    stream = (HPDF_Stream)HPDF_GetMem (mmgr, sizeof(HPDF_Stream_Rec));

    if (stream) {
        HPDF_MemSet (stream, 0, sizeof(HPDF_Stream_Rec));
        stream->sig_bytes = HPDF_STREAM_SIG_BYTES;
        stream->error = mmgr->error;
        stream->mmgr = mmgr;
        stream->read_fn = read_fn;
        stream->seek_fn = seek_fn;
        stream->tell_fn = tell_fn;
        stream->size_fn = size_fn;
        stream->attr = data;
        stream->type = HPDF_STREAM_CALLBACK;
    }

    return stream;
}