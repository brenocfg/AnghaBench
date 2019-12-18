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
struct TYPE_4__ {scalar_t__ w_ptr_tx; scalar_t__ r_ptr_tx; } ;
typedef  TYPE_1__ uart_ring ;

/* Variables and functions */
 int /*<<< orphan*/  uart_tx_ring (TYPE_1__*) ; 

void uart_flush_sync(uart_ring *q) {
  // empty the TX buffer
  while (q->w_ptr_tx != q->r_ptr_tx) {
    uart_tx_ring(q);
  }
}