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
struct dmi_system_id {scalar_t__ driver_data; } ;

/* Variables and functions */
 unsigned int DEFAULT_UARTCLK ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_uart_dmi_table ; 
 unsigned int user_uartclk ; 

__attribute__((used)) static unsigned int pch_uart_get_uartclk(void)
{
	const struct dmi_system_id *d;

	if (user_uartclk)
		return user_uartclk;

	d = dmi_first_match(pch_uart_dmi_table);
	if (d)
		return (unsigned long)d->driver_data;

	return DEFAULT_UARTCLK;
}