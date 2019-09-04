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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void print_usage(void)
{
	fprintf(stderr, "Usage: lsgpio [options]...\n"
		"List GPIO chips, lines and states\n"
		"  -n <name>  List GPIOs on a named device\n"
		"  -?         This helptext\n"
	);
}