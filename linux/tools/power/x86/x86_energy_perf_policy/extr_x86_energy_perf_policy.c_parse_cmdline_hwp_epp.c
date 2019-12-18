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
 int HWP_EPP_BALANCE_PERFORMANCE ; 
 int HWP_EPP_BALANCE_POWERSAVE ; 
 int HWP_EPP_PERFORMANCE ; 
 int HWP_EPP_POWERSAVE ; 
#define  OPTARG_BALANCE_PERFORMANCE 132 
#define  OPTARG_BALANCE_POWER 131 
#define  OPTARG_NORMAL 130 
#define  OPTARG_PERFORMANCE 129 
#define  OPTARG_POWER 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int update_hwp_epp ; 
 int /*<<< orphan*/  usage () ; 

int parse_cmdline_hwp_epp(int i)
{
	update_hwp_epp = 1;

	switch (i) {
	case OPTARG_POWER:
		return HWP_EPP_POWERSAVE;
	case OPTARG_BALANCE_POWER:
		return HWP_EPP_BALANCE_POWERSAVE;
	case OPTARG_NORMAL:
	case OPTARG_BALANCE_PERFORMANCE:
		return HWP_EPP_BALANCE_PERFORMANCE;
	case OPTARG_PERFORMANCE:
		return HWP_EPP_PERFORMANCE;
	}
	if (i < 0 || i > 0xff) {
		fprintf(stderr, "--hwp-epp must be from 0 to 0xff\n");
		usage();
	}
	return i;
}