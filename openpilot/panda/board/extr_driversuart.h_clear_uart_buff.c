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
struct TYPE_3__ {scalar_t__ r_ptr_rx; scalar_t__ w_ptr_rx; scalar_t__ r_ptr_tx; scalar_t__ w_ptr_tx; } ;
typedef  TYPE_1__ uart_ring ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL () ; 
 int /*<<< orphan*/  EXIT_CRITICAL () ; 

void clear_uart_buff(uart_ring *q) {
  ENTER_CRITICAL();
  q->w_ptr_tx = 0;
  q->r_ptr_tx = 0;
  q->w_ptr_rx = 0;
  q->r_ptr_rx = 0;
  EXIT_CRITICAL();
}