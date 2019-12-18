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
typedef  scalar_t__ coap_tick_t ;
struct TYPE_3__ {scalar_t__ t; } ;
typedef  TYPE_1__ coap_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  coap_timer_elapsed (scalar_t__*) ; 

void coap_timer_update(coap_queue_t ** queue){
  if (!queue)
    return;
  coap_tick_t diff = 0;
  coap_queue_t *first = *queue;
  coap_timer_elapsed(&diff); // update: basetime = now, diff = now - oldbase, means time elapsed
  if (first) {
    // diff ms time is elapsed, re-calculate the first node->t
    if (first->t >= diff){
      first->t -= diff;
    } else {
      first->t = 0;  // when timer enabled, time out almost immediately
    }
  }
}