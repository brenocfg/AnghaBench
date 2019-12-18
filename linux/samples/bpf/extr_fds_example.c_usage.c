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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
	printf("Usage: fds_example [...]\n");
	printf("       -F <file>   File to pin/get object\n");
	printf("       -P          |- pin object\n");
	printf("       -G          `- get object\n");
	printf("       -m          eBPF map mode\n");
	printf("       -k <key>    |- map key\n");
	printf("       -v <value>  `- map value\n");
	printf("       -p          eBPF prog mode\n");
	printf("       -o <object> `- object file\n");
	printf("       -h          Display this help.\n");
}