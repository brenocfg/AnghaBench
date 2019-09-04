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
typedef  int uint32_t ;
struct ioc3_port {TYPE_1__* ip_card; int /*<<< orphan*/  ip_idd; int /*<<< orphan*/  ip_is; } ;
struct TYPE_2__ {int ic_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc3_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void disable_intrs(struct ioc3_port *port, uint32_t mask)
{
	if (port->ip_card->ic_enable & mask) {
		ioc3_disable(port->ip_is, port->ip_idd, mask);
		port->ip_card->ic_enable &= ~mask;
	}
}