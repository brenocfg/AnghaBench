#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {long long timestamp_eof; } ;
typedef  TYPE_1__ VIPCBufExtra ;
struct TYPE_15__ {int opening; int rotating; int segment; int next_segment; int counter; int width; int dirty; int closing; int /*<<< orphan*/  lock; int /*<<< orphan*/  done_out; int /*<<< orphan*/  handle; int /*<<< orphan*/  height; int /*<<< orphan*/ * v_ptr2; int /*<<< orphan*/ * u_ptr2; int /*<<< orphan*/ * y_ptr2; scalar_t__ downscale; int /*<<< orphan*/  next_path; int /*<<< orphan*/  free_in; int /*<<< orphan*/  open; } ;
struct TYPE_14__ {long long nTimeStamp; scalar_t__ nOffset; int /*<<< orphan*/  nFlags; int /*<<< orphan*/  nFilledLen; int /*<<< orphan*/ * pBuffer; } ;
typedef  TYPE_2__ OMX_BUFFERHEADERTYPE ;
typedef  TYPE_3__ EncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_FMT_NV12 ; 
 int /*<<< orphan*/  I420Scale (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int I420ToNV12 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_ENDOFFRAME ; 
 int OMX_EmptyThisBuffer (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int OMX_ErrorNone ; 
 int /*<<< orphan*/  VENUS_BUFFER_SIZE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int VENUS_UV_STRIDE (int /*<<< orphan*/ ,int) ; 
 int VENUS_Y_SCANLINES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VENUS_Y_STRIDE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  encoder_close (TYPE_3__*) ; 
 int /*<<< orphan*/  encoder_open (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_out_buf (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  kFilterNone ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* queue_pop (int /*<<< orphan*/ *) ; 
 TYPE_2__* queue_try_pop (int /*<<< orphan*/ *) ; 

int encoder_encode_frame(EncoderState *s,
                         const uint8_t *y_ptr, const uint8_t *u_ptr, const uint8_t *v_ptr,
                         int in_width, int in_height,
                         int *frame_segment, VIPCBufExtra *extra) {
  int err;
  pthread_mutex_lock(&s->lock);

  if (s->opening) {
    encoder_open(s, s->next_path);
    s->opening = false;
  }

  if (!s->open) {
    pthread_mutex_unlock(&s->lock);
    return -1;
  }

  // this sometimes freezes... put it outside the encoder lock so we can still trigger rotates...
  // THIS IS A REALLY BAD IDEA, but apparently the race has to happen 30 times to trigger this
  pthread_mutex_unlock(&s->lock);
  OMX_BUFFERHEADERTYPE* in_buf = queue_pop(&s->free_in);
  pthread_mutex_lock(&s->lock);

  if (s->rotating) {
    encoder_close(s);
    encoder_open(s, s->next_path);
    s->segment = s->next_segment;
    s->rotating = false;
  }

  int ret = s->counter;

  uint8_t *in_buf_ptr = in_buf->pBuffer;
  // printf("in_buf ptr %p\n", in_buf_ptr);

  uint8_t *in_y_ptr = in_buf_ptr;
  int in_y_stride = VENUS_Y_STRIDE(COLOR_FMT_NV12, s->width);
  int in_uv_stride = VENUS_UV_STRIDE(COLOR_FMT_NV12, s->width);
  // uint8_t *in_uv_ptr = in_buf_ptr + (s->width * s->height);
  uint8_t *in_uv_ptr = in_buf_ptr + (in_y_stride * VENUS_Y_SCANLINES(COLOR_FMT_NV12, s->height));

  if (s->downscale) {
    I420Scale(y_ptr, in_width,
              u_ptr, in_width/2,
              v_ptr, in_width/2,
              in_width, in_height,
              s->y_ptr2, s->width,
              s->u_ptr2, s->width/2,
              s->v_ptr2, s->width/2,
              s->width, s->height,
              kFilterNone);
    y_ptr = s->y_ptr2;
    u_ptr = s->u_ptr2;
    v_ptr = s->v_ptr2;
  }
  err = I420ToNV12(y_ptr, s->width,
                   u_ptr, s->width/2,
                   v_ptr, s->width/2,
                   in_y_ptr, in_y_stride,
                   in_uv_ptr, in_uv_stride,
                   s->width, s->height);
  assert(err == 0);

  // in_buf->nFilledLen = (s->width*s->height) + (s->width*s->height/2);
  in_buf->nFilledLen = VENUS_BUFFER_SIZE(COLOR_FMT_NV12, s->width, s->height);
  in_buf->nFlags = OMX_BUFFERFLAG_ENDOFFRAME;
  in_buf->nOffset = 0;
  in_buf->nTimeStamp = extra->timestamp_eof/1000LL;  // OMX_TICKS, in microseconds

  err = OMX_EmptyThisBuffer(s->handle, in_buf);
  assert(err == OMX_ErrorNone);

  // pump output
  while (true) {
    OMX_BUFFERHEADERTYPE *out_buf = queue_try_pop(&s->done_out);
    if (!out_buf) {
      break;
    }
    handle_out_buf(s, out_buf);
  }

  s->dirty = true;

  s->counter++;

  if (frame_segment) {
    *frame_segment = s->segment;
  }

  if (s->closing) {
    encoder_close(s);
    s->closing = false;
  }

  pthread_mutex_unlock(&s->lock);
  return ret;
}