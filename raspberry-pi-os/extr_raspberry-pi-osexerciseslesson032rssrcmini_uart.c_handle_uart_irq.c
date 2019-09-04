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

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IIR_REG ; 
 int /*<<< orphan*/  AUX_MU_IO_REG ; 
 int /*<<< orphan*/  MU_IIR_RX_CLR ; 
 int MU_IIR_RX_READY ; 
 int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_send (char) ; 

void handle_uart_irq(void) {
  if (get32(AUX_MU_IIR_REG) & MU_IIR_RX_READY) {
    char c = get32(AUX_MU_IO_REG) & 0xFF;
    put32(AUX_MU_IIR_REG, MU_IIR_RX_CLR);

    uart_send(c);
  }
}