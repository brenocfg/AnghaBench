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
struct cyclades_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int serial_paranoia_check(struct cyclades_port *info,
		const char *name, const char *routine)
{
#ifdef SERIAL_PARANOIA_CHECK
	if (!info) {
		printk(KERN_WARNING "cyc Warning: null cyclades_port for (%s) "
				"in %s\n", name, routine);
		return 1;
	}

	if (info->magic != CYCLADES_MAGIC) {
		printk(KERN_WARNING "cyc Warning: bad magic number for serial "
				"struct (%s) in %s\n", name, routine);
		return 1;
	}
#endif
	return 0;
}