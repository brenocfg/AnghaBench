#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pb; } ;
struct TYPE_11__ {int open; int dirty; int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_path; int /*<<< orphan*/  of; TYPE_7__* ofmt_ctx; scalar_t__ remuxing; int /*<<< orphan*/  done_out; int /*<<< orphan*/  handle; int /*<<< orphan*/  free_in; } ;
struct TYPE_10__ {int nFlags; scalar_t__ nTimeStamp; scalar_t__ nOffset; scalar_t__ nFilledLen; } ;
typedef  TYPE_1__ OMX_BUFFERHEADERTYPE ;
typedef  TYPE_2__ EncoderState ;

/* Variables and functions */
 int OMX_BUFFERFLAG_EOS ; 
 int OMX_EmptyThisBuffer (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int OMX_ErrorNone ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  av_write_trailer (TYPE_7__*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_7__*) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_out_buf (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* queue_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void encoder_close(EncoderState *s) {
  int err;

  pthread_mutex_lock(&s->lock);

  if (s->open) {
    if (s->dirty) {
      // drain output only if there could be frames in the encoder

      OMX_BUFFERHEADERTYPE* in_buf = queue_pop(&s->free_in);
      in_buf->nFilledLen = 0;
      in_buf->nOffset = 0;
      in_buf->nFlags = OMX_BUFFERFLAG_EOS;
      in_buf->nTimeStamp = 0;

      err = OMX_EmptyThisBuffer(s->handle, in_buf);
      assert(err == OMX_ErrorNone);

      while (true) {
        OMX_BUFFERHEADERTYPE *out_buf = queue_pop(&s->done_out);

        handle_out_buf(s, out_buf);

        if (out_buf->nFlags & OMX_BUFFERFLAG_EOS) {
          break;
        }
      }
      s->dirty = false;
    }

    if (s->remuxing) {
      av_write_trailer(s->ofmt_ctx);
      avio_closep(&s->ofmt_ctx->pb);
      avformat_free_context(s->ofmt_ctx);
    } else {
      fclose(s->of);
    }
    unlink(s->lock_path);
  }
  s->open = false;

  pthread_mutex_unlock(&s->lock);
}