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

__attribute__((used)) static int w1_f23_add_slave(struct w1_slave *sl)
{
#ifdef CONFIG_W1_SLAVE_DS2433_CRC
	struct w1_f23_data *data;

	data = kzalloc(sizeof(struct w1_f23_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	sl->family_data = data;

#endif	/* CONFIG_W1_SLAVE_DS2433_CRC */
	return 0;
}