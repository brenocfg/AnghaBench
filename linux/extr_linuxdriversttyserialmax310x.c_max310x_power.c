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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX310X_MODE1_FORCESLEEP_BIT ; 
 int /*<<< orphan*/  MAX310X_MODE1_REG ; 
 int /*<<< orphan*/  max310x_port_update (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void max310x_power(struct uart_port *port, int on)
{
	max310x_port_update(port, MAX310X_MODE1_REG,
			    MAX310X_MODE1_FORCESLEEP_BIT,
			    on ? 0 : MAX310X_MODE1_FORCESLEEP_BIT);
	if (on)
		msleep(50);
}