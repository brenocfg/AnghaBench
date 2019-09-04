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
struct w1_slave {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void w1_f23_remove_slave(struct w1_slave *sl)
{
#ifdef CONFIG_W1_SLAVE_DS2433_CRC
	kfree(sl->family_data);
	sl->family_data = NULL;
#endif	/* CONFIG_W1_SLAVE_DS2433_CRC */
}