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
#define  OPTARG_BALANCE_PERFORMANCE 132 
#define  OPTARG_BALANCE_POWER 131 
#define  OPTARG_NORMAL 130 
#define  OPTARG_PERFORMANCE 129 
#define  OPTARG_POWER 128 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int update_hwp_window ; 
 int /*<<< orphan*/  usage () ; 

int parse_cmdline_hwp_window(int i)
{
	unsigned int exponent;

	update_hwp_window = 1;

	switch (i) {
	case OPTARG_POWER:
	case OPTARG_BALANCE_POWER:
	case OPTARG_NORMAL:
	case OPTARG_BALANCE_PERFORMANCE:
	case OPTARG_PERFORMANCE:
		return 0;
	}
	if (i < 0 || i > 1270000000) {
		fprintf(stderr, "--hwp-window: 0 for auto; 1 - 1270000000 usec for window duration\n");
		usage();
	}
	for (exponent = 0; ; ++exponent) {
		if (debug)
			printf("%d 10^%d\n", i, exponent);

		if (i <= 127)
			break;

		i = i / 10;
	}
	if (debug)
		fprintf(stderr, "%d*10^%d: 0x%x\n", i, exponent, (exponent << 7) | i);

	return (exponent << 7) | i;
}