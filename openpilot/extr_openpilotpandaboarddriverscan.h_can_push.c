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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ w_ptr; scalar_t__ fifo_size; scalar_t__ r_ptr; int /*<<< orphan*/ * elems; } ;
typedef  TYPE_1__ can_ring ;
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  enter_critical_section () ; 
 int /*<<< orphan*/  exit_critical_section () ; 
 int /*<<< orphan*/  puts (char*) ; 

int can_push(can_ring *q, CAN_FIFOMailBox_TypeDef *elem) {
  int ret = 0;
  uint32_t next_w_ptr;

  enter_critical_section();
  if ((q->w_ptr + 1) == q->fifo_size) next_w_ptr = 0;
  else next_w_ptr = q->w_ptr + 1;
  if (next_w_ptr != q->r_ptr) {
    q->elems[q->w_ptr] = *elem;
    q->w_ptr = next_w_ptr;
    ret = 1;
  }
  exit_critical_section();
  if (ret == 0) puts("can_push failed!\n");
  return ret;
}