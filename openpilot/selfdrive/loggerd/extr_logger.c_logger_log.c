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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ cur_handle; } ;
typedef  TYPE_1__ LoggerState ;

/* Variables and functions */
 int /*<<< orphan*/  lh_log (scalar_t__,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void logger_log(LoggerState *s, uint8_t* data, size_t data_size, bool in_qlog) {
  pthread_mutex_lock(&s->lock);
  if (s->cur_handle) {
    lh_log(s->cur_handle, data, data_size, in_qlog);
  }
  pthread_mutex_unlock(&s->lock);
}