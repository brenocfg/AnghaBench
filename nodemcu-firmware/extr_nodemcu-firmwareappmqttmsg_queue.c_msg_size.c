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
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ msg_queue_t ;

/* Variables and functions */

int msg_size(msg_queue_t **head){
  if(!head || !*head){
    return 0;
  }
  int i = 1;
  msg_queue_t *tail = *head;
  if(tail){
    while(tail->next!=NULL){
      tail = tail->next;
      i++;
    }
  }
  return i;
}