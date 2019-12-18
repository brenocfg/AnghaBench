#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_in_bufs; int num_out_bufs; int /*<<< orphan*/ * v_ptr2; int /*<<< orphan*/ * u_ptr2; int /*<<< orphan*/ * y_ptr2; scalar_t__ downscale; int /*<<< orphan*/  handle; int /*<<< orphan*/ * out_buf_headers; int /*<<< orphan*/ * in_buf_headers; int /*<<< orphan*/  open; } ;
typedef  TYPE_1__ EncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_CommandStateSet ; 
 int OMX_ErrorNone ; 
 int OMX_FreeBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OMX_FreeHandle (int /*<<< orphan*/ ) ; 
 int OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMX_StateIdle ; 
 int /*<<< orphan*/  OMX_StateLoaded ; 
 int /*<<< orphan*/  PORT_INDEX_IN ; 
 int /*<<< orphan*/  PORT_INDEX_OUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

void encoder_destroy(EncoderState *s) {
  int err;

  assert(!s->open);

  err = OMX_SendCommand(s->handle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  assert(err == OMX_ErrorNone);

  wait_for_state(s, OMX_StateIdle);

  err = OMX_SendCommand(s->handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);
  assert(err == OMX_ErrorNone);

  for (int i=0; i<s->num_in_bufs; i++) {
    err = OMX_FreeBuffer(s->handle, PORT_INDEX_IN, s->in_buf_headers[i]);
    assert(err == OMX_ErrorNone);
  }
  free(s->in_buf_headers);

  for (int i=0; i<s->num_out_bufs; i++) {
    err = OMX_FreeBuffer(s->handle, PORT_INDEX_OUT, s->out_buf_headers[i]);
    assert(err == OMX_ErrorNone);
  }
  free(s->out_buf_headers);

  wait_for_state(s, OMX_StateLoaded);

  err = OMX_FreeHandle(s->handle);
  assert(err == OMX_ErrorNone);

  if (s->downscale) {
    free(s->y_ptr2);
    free(s->u_ptr2);
    free(s->v_ptr2);
  }
}