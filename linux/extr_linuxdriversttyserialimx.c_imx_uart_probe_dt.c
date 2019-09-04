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
struct platform_device {int dummy; } ;
struct imx_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int imx_uart_probe_dt(struct imx_port *sport,
				    struct platform_device *pdev)
{
	return 1;
}