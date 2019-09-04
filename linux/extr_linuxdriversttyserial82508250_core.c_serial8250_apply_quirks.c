#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  quirks; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPQ_NO_TXEN_TEST ; 
 scalar_t__ skip_txen_test ; 

__attribute__((used)) static inline void serial8250_apply_quirks(struct uart_8250_port *up)
{
	up->port.quirks |= skip_txen_test ? UPQ_NO_TXEN_TEST : 0;
}