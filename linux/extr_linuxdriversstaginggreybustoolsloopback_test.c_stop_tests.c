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
struct loopback_test {int device_count; TYPE_1__* devices; } ;
struct TYPE_2__ {int /*<<< orphan*/  sysfs_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_enabled (struct loopback_test*,int) ; 
 int /*<<< orphan*/  write_sysfs_val (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_tests(struct loopback_test *t)
{
	int i;

	for (i = 0; i < t->device_count; i++) {
		if (!device_enabled(t, i))
			continue;
		write_sysfs_val(t->devices[i].sysfs_entry, "type", 0);
	}
}