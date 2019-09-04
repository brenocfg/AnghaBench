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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int update_turbo ; 
 int /*<<< orphan*/  usage () ; 

int parse_cmdline_turbo(int i)
{
	update_turbo = 1;

	switch (i) {
	case OPTARG_POWER:
		return 0;
	case OPTARG_NORMAL:
	case OPTARG_BALANCE_POWER:
	case OPTARG_BALANCE_PERFORMANCE:
	case OPTARG_PERFORMANCE:
		return 1;
	}
	if (i < 0 || i > 1) {
		fprintf(stderr, "--turbo-enable: 1 to enable, 0 to disable\n");
		usage();
	}
	return i;
}