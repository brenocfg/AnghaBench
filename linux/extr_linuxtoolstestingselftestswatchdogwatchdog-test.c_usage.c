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
 int DEFAULT_PING_RATE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage(char *progname)
{
	printf("Usage: %s [options]\n", progname);
	printf(" -b, --bootstatus    Get last boot status (Watchdog/POR)\n");
	printf(" -d, --disable       Turn off the watchdog timer\n");
	printf(" -e, --enable        Turn on the watchdog timer\n");
	printf(" -h, --help          Print the help message\n");
	printf(" -p, --pingrate=P    Set ping rate to P seconds (default %d)\n", DEFAULT_PING_RATE);
	printf(" -t, --timeout=T     Set timeout to T seconds\n");
	printf("\n");
	printf("Parameters are parsed left-to-right in real-time.\n");
	printf("Example: %s -d -t 10 -p 5 -e\n", progname);
}