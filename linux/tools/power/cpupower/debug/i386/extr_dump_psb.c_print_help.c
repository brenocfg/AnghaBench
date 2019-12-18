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

void print_help(void)
{
	printf ("Usage: dump_psb [options]\n");
	printf ("Options:\n");
	printf ("  -n, --numpst     Set number of PST tables to scan\n");
	printf ("  -r, --relevant   Only display PSTs relevant to cpuid N\n");
}