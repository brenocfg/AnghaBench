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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(char *progname)
{
	fprintf(stderr,
		"usage: %s [options]\n"
		" -c         query the ptp clock's capabilities\n"
		" -d name    device to open\n"
		" -e val     read 'val' external time stamp events\n"
		" -f val     adjust the ptp clock frequency by 'val' ppb\n"
		" -g         get the ptp clock time\n"
		" -h         prints this message\n"
		" -i val     index for event/trigger\n"
		" -k val     measure the time offset between system and phc clock\n"
		"            for 'val' times (Maximum 25)\n"
		" -l         list the current pin configuration\n"
		" -L pin,val configure pin index 'pin' with function 'val'\n"
		"            the channel index is taken from the '-i' option\n"
		"            'val' specifies the auxiliary function:\n"
		"            0 - none\n"
		"            1 - external time stamp\n"
		"            2 - periodic output\n"
		" -p val     enable output with a period of 'val' nanoseconds\n"
		" -P val     enable or disable (val=1|0) the system clock PPS\n"
		" -s         set the ptp clock time from the system time\n"
		" -S         set the system time from the ptp clock time\n"
		" -t val     shift the ptp clock time by 'val' seconds\n"
		" -T val     set the ptp clock time to 'val' seconds\n",
		progname);
}