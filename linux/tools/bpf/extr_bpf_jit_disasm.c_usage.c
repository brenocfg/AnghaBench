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
	printf("Usage: bpf_jit_disasm [...]\n");
	printf("       -o          Also display related opcodes (default: off).\n");
	printf("       -O <file>   Write binary image of code to file, don't disassemble to stdout.\n");
	printf("       -f <file>   Read last image dump from file or stdin (default: klog).\n");
	printf("       -h          Display this help.\n");
}