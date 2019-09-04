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
 int bus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_bus_type ; 
 int /*<<< orphan*/  tb_xdomain_exit () ; 
 int tb_xdomain_init () ; 

int tb_domain_init(void)
{
	int ret;

	ret = tb_xdomain_init();
	if (ret)
		return ret;
	ret = bus_register(&tb_bus_type);
	if (ret)
		tb_xdomain_exit();

	return ret;
}