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
struct r_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int rocket_paranoia_check(struct r_port *info,
					const char *routine)
{
#ifdef ROCKET_PARANOIA_CHECK
	if (!info)
		return 1;
	if (info->magic != RPORT_MAGIC) {
		printk(KERN_WARNING "Warning: bad magic number for rocketport "
				"struct in %s\n", routine);
		return 1;
	}
#endif
	return 0;
}