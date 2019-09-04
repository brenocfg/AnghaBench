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
typedef  int /*<<< orphan*/  u32 ;
struct imx_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCR2_CTSC ; 

__attribute__((used)) static void imx_uart_rts_auto(struct imx_port *sport, u32 *ucr2)
{
	*ucr2 |= UCR2_CTSC;
}