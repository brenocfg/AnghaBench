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
typedef  int /*<<< orphan*/  msg_queue_t ;

/* Variables and functions */

msg_queue_t * msg_peek(msg_queue_t **head){
  if(!head || !*head){
    return NULL;
  }
  return *head;  // fetch head.
}