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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ coap_queue_t ;

/* Variables and functions */

coap_queue_t * coap_pop_next( coap_queue_t **queue ) {		// this function is called inside timeout callback only.
  coap_queue_t *next;

  if ( !(*queue) )
    return NULL;

  next = *queue;
  *queue = (*queue)->next;
  // if (queue) {
  //   queue->t += next->t;
  // }
  next->next = NULL;
  return next;
}