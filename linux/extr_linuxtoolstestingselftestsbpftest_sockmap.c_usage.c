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
struct TYPE_2__ {char* name; int* flag; int val; } ;

/* Variables and functions */
 TYPE_1__* long_options ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage(char *argv[])
{
	int i;

	printf(" Usage: %s --cgroup <cgroup_path>\n", argv[0]);
	printf(" options:\n");
	for (i = 0; long_options[i].name != 0; i++) {
		printf(" --%-12s", long_options[i].name);
		if (long_options[i].flag != NULL)
			printf(" flag (internal value:%d)\n",
				*long_options[i].flag);
		else
			printf(" -%c\n", long_options[i].val);
	}
	printf("\n");
}