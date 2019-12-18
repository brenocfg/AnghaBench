#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state_cv; } ;
typedef  scalar_t__ OMX_STATETYPE ;
typedef  TYPE_1__ EncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_for_state(EncoderState *s, OMX_STATETYPE state) {
  pthread_mutex_lock(&s->state_lock);
  while (s->state != state) {
    pthread_cond_wait(&s->state_cv, &s->state_lock);
  }
  pthread_mutex_unlock(&s->state_lock);
}