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
struct s_smc {int dummy; } ;

/* Variables and functions */

void ecm_state_change(struct s_smc *smc, int e_state)
{
#ifdef DRIVERDEBUG
	char *s;

	switch (e_state) {
	case EC0_OUT:
		s = "EC0_OUT";
		break;
	case EC1_IN:
		s = "EC1_IN";
		break;
	case EC2_TRACE:
		s = "EC2_TRACE";
		break;
	case EC3_LEAVE:
		s = "EC3_LEAVE";
		break;
	case EC4_PATH_TEST:
		s = "EC4_PATH_TEST";
		break;
	case EC5_INSERT:
		s = "EC5_INSERT";
		break;
	case EC6_CHECK:
		s = "EC6_CHECK";
		break;
	case EC7_DEINSERT:
		s = "EC7_DEINSERT";
		break;
	default:
		s = "unknown";
		break;
	}
	pr_debug("ecm_state_change: %s\n", s);
#endif				//DRIVERDEBUG
}