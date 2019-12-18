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
	printf(" -f, --file\t\tOpen watchdog device file\n");
	printf("\t\t\tDefault is /dev/watchdog\n");
	printf(" -i, --info\t\tShow watchdog_info\n");
	printf(" -b, --bootstatus\tGet last boot status (Watchdog/POR)\n");
	printf(" -d, --disable\t\tTurn off the watchdog timer\n");
	printf(" -e, --enable\t\tTurn on the watchdog timer\n");
	printf(" -h, --help\t\tPrint the help message\n");
	printf(" -p, --pingrate=P\tSet ping rate to P seconds (default %d)\n",
	       DEFAULT_PING_RATE);
	printf(" -t, --timeout=T\tSet timeout to T seconds\n");
	printf(" -T, --gettimeout\tGet the timeout\n");
	printf(" -n, --pretimeout=T\tSet the pretimeout to T seconds\n");
	printf(" -N, --getpretimeout\tGet the pretimeout\n");
	printf(" -L, --gettimeleft\tGet the time left until timer expires\n");
	printf("\n");
	printf("Parameters are parsed left-to-right in real-time.\n");
	printf("Example: %s -d -t 10 -p 5 -e\n", progname);
	printf("Example: %s -t 12 -T -n 7 -N\n", progname);
}