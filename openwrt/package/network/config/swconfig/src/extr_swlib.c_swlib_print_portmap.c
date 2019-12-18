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
struct switch_dev {int cpu_port; int ports; char* dev_name; char* name; TYPE_1__* maps; } ;
struct TYPE_2__ {char* segment; int virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void
swlib_print_portmap(struct switch_dev *dev, char *segment)
{
	int i;

	if (segment) {
		if (!strcmp(segment, "cpu")) {
			printf("%d ", dev->cpu_port);
		} else if (!strcmp(segment, "disabled")) {
			for (i = 0; i < dev->ports; i++)
				if (!dev->maps[i].segment)
					printf("%d ", i);
		} else for (i = 0; i < dev->ports; i++) {
			if (dev->maps[i].segment && !strcmp(dev->maps[i].segment, segment))
				printf("%d ", i);
		}
	} else {
		printf("%s - %s\n", dev->dev_name, dev->name);
		for (i = 0; i < dev->ports; i++)
			if (i == dev->cpu_port)
				printf("port%d:\tcpu\n", i);
			else if (dev->maps[i].segment)
				printf("port%d:\t%s.%d\n", i, dev->maps[i].segment, dev->maps[i].virt);
			else
				printf("port%d:\tdisabled\n", i);
	}
}