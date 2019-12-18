#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state_cv; } ;
typedef  int OMX_U32 ;
typedef  TYPE_1__* OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_HANDLETYPE ;
typedef  int OMX_EVENTTYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ EncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,int) ; 
 int /*<<< orphan*/  LOGE (char*,int) ; 
 int OMX_CommandStateSet ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
#define  OMX_EventCmdComplete 129 
#define  OMX_EventError 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OMX_ERRORTYPE event_handler(OMX_HANDLETYPE component, OMX_PTR app_data, OMX_EVENTTYPE event,
                                   OMX_U32 data1, OMX_U32 data2, OMX_PTR event_data) {
  EncoderState *s = app_data;

  switch (event) {
  case OMX_EventCmdComplete:
    assert(data1 == OMX_CommandStateSet);
    LOG("set state event 0x%x", data2);
    pthread_mutex_lock(&s->state_lock);
    s->state = data2;
    pthread_cond_broadcast(&s->state_cv);
    pthread_mutex_unlock(&s->state_lock);
    break;
  case OMX_EventError:
    LOGE("OMX error 0x%08x", data1);
    // assert(false);
    break;
  default:
    LOGE("unhandled event %d", event);
    assert(false);
    break;
  }

  pthread_mutex_unlock(&s->state_lock);

  return OMX_ErrorNone;
}