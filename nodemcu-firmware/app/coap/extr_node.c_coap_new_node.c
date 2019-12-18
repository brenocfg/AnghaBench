#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  coap_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/ * coap_malloc_node () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

coap_queue_t * coap_new_node(void) {
  coap_queue_t *node;
  node = coap_malloc_node();

  if ( ! node ) {
    return NULL;
  }

  memset(node, 0, sizeof(*node));
  return node;
}