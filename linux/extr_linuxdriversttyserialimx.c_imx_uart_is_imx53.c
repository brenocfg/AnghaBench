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
struct TYPE_2__ {scalar_t__ devtype; } ;

/* Variables and functions */
 scalar_t__ IMX53_UART ; 

__attribute__((used)) static inline int imx_uart_is_imx53(struct imx_port *sport)
{
	return sport->devdata->devtype == IMX53_UART;
}