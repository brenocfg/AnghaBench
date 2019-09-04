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
	fprintf(stderr, "Usage: generic_buffer [options]...\n"
		"Capture, convert and output data from IIO device buffer\n"
		"  -a         Auto-activate all available channels\n"
		"  -A         Force-activate ALL channels\n"
		"  -c <n>     Do n conversions, or loop forever if n < 0\n"
		"  -e         Disable wait for event (new data)\n"
		"  -g         Use trigger-less mode\n"
		"  -l <n>     Set buffer length to n samples\n"
		"  --device-name -n <name>\n"
		"  --device-num -N <num>\n"
		"        Set device by name or number (mandatory)\n"
		"  --trigger-name -t <name>\n"
		"  --trigger-num -T <num>\n"
		"        Set trigger by name or number\n"
		"  -w <n>     Set delay between reads in us (event-less mode)\n");
}