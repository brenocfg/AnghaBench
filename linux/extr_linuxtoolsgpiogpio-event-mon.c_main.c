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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ GPIOEVENT_REQUEST_BOTH_EDGES ; 
 scalar_t__ GPIOEVENT_REQUEST_FALLING_EDGE ; 
 scalar_t__ GPIOEVENT_REQUEST_RISING_EDGE ; 
 scalar_t__ GPIOHANDLE_REQUEST_INPUT ; 
 scalar_t__ GPIOHANDLE_REQUEST_OPEN_DRAIN ; 
 scalar_t__ GPIOHANDLE_REQUEST_OPEN_SOURCE ; 
 int getopt (int,char**,char*) ; 
 int monitor_device (char const*,unsigned int,scalar_t__,scalar_t__,unsigned int) ; 
 char* optarg ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  printf (char*) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 

int main(int argc, char **argv)
{
	const char *device_name = NULL;
	unsigned int line = -1;
	unsigned int loops = 0;
	uint32_t handleflags = GPIOHANDLE_REQUEST_INPUT;
	uint32_t eventflags = 0;
	int c;

	while ((c = getopt(argc, argv, "c:n:o:dsrf?")) != -1) {
		switch (c) {
		case 'c':
			loops = strtoul(optarg, NULL, 10);
			break;
		case 'n':
			device_name = optarg;
			break;
		case 'o':
			line = strtoul(optarg, NULL, 10);
			break;
		case 'd':
			handleflags |= GPIOHANDLE_REQUEST_OPEN_DRAIN;
			break;
		case 's':
			handleflags |= GPIOHANDLE_REQUEST_OPEN_SOURCE;
			break;
		case 'r':
			eventflags |= GPIOEVENT_REQUEST_RISING_EDGE;
			break;
		case 'f':
			eventflags |= GPIOEVENT_REQUEST_FALLING_EDGE;
			break;
		case '?':
			print_usage();
			return -1;
		}
	}

	if (!device_name || line == -1) {
		print_usage();
		return -1;
	}
	if (!eventflags) {
		printf("No flags specified, listening on both rising and "
		       "falling edges\n");
		eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
	}
	return monitor_device(device_name, line, handleflags,
			      eventflags, loops);
}