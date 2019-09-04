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
typedef  int uint16_t ;
struct TYPE_3__ {int w_ptr_rx; int r_ptr_rx; char* elems_rx; } ;
typedef  TYPE_1__ uart_ring ;

/* Variables and functions */
 int FIFO_SIZE ; 
 int /*<<< orphan*/  enter_critical_section () ; 
 int /*<<< orphan*/  exit_critical_section () ; 

int injectc(uart_ring *q, char elem) {
  int ret = 0;
  uint16_t next_w_ptr;

  enter_critical_section();
  next_w_ptr = (q->w_ptr_rx + 1) % FIFO_SIZE;
  if (next_w_ptr != q->r_ptr_rx) {
    q->elems_rx[q->w_ptr_rx] = elem;
    q->w_ptr_rx = next_w_ptr;
    ret = 1;
  }
  exit_critical_section();

  return ret;
}