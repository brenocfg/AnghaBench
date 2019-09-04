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
 int GPIOHANDLES_MAX ; 
 int getopt (int,char**,char*) ; 
 int hammer_device (char const*,unsigned int*,int,unsigned int) ; 
 char* optarg ; 
 int /*<<< orphan*/  print_usage () ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 

int main(int argc, char **argv)
{
	const char *device_name = NULL;
	unsigned int lines[GPIOHANDLES_MAX];
	unsigned int loops = 0;
	int nlines;
	int c;
	int i;

	i = 0;
	while ((c = getopt(argc, argv, "c:n:o:?")) != -1) {
		switch (c) {
		case 'c':
			loops = strtoul(optarg, NULL, 10);
			break;
		case 'n':
			device_name = optarg;
			break;
		case 'o':
			lines[i] = strtoul(optarg, NULL, 10);
			i++;
			break;
		case '?':
			print_usage();
			return -1;
		}
	}
	nlines = i;

	if (!device_name || !nlines) {
		print_usage();
		return -1;
	}
	return hammer_device(device_name, lines, nlines, loops);
}