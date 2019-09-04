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
struct imx_port {TYPE_1__* devdata; } ;
struct TYPE_2__ {int uts_reg; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned imx_uart_uts_reg(struct imx_port *sport)
{
	return sport->devdata->uts_reg;
}