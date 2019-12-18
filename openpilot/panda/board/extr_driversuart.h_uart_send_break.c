#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* uart; } ;
typedef  TYPE_2__ uart_ring ;
struct TYPE_4__ {int CR1; } ;

/* Variables and functions */
 int USART_CR1_SBK ; 

void uart_send_break(uart_ring *u) {
  while ((u->uart->CR1 & USART_CR1_SBK) != 0);
  u->uart->CR1 |= USART_CR1_SBK;
}