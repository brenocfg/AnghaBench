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
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void show_loopback_devices(struct loopback_test *t)
{
	int i;

	if (t->device_count == 0) {
		printf("No loopback devices.\n");
		return;
	}

	for (i = 0; i < t->device_count; i++)
		printf("device[%d] = %s\n", i, t->devices[i].name);

}