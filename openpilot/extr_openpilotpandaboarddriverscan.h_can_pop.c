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
struct TYPE_3__ {size_t w_ptr; size_t r_ptr; int fifo_size; int /*<<< orphan*/ * elems; } ;
typedef  TYPE_1__ can_ring ;
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  enter_critical_section () ; 
 int /*<<< orphan*/  exit_critical_section () ; 

int can_pop(can_ring *q, CAN_FIFOMailBox_TypeDef *elem) {
  int ret = 0;

  enter_critical_section();
  if (q->w_ptr != q->r_ptr) {
    *elem = q->elems[q->r_ptr];
    if ((q->r_ptr + 1) == q->fifo_size) q->r_ptr = 0;
    else q->r_ptr += 1;
    ret = 1;
  }
  exit_critical_section();

  return ret;
}