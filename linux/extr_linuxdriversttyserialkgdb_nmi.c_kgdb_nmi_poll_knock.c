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
 int NO_POLL_CHAR ; 
 scalar_t__ kgdb_nmi_knock ; 
 int kgdb_nmi_poll_one_knock () ; 

bool kgdb_nmi_poll_knock(void)
{
	if (kgdb_nmi_knock < 0)
		return true;

	while (1) {
		int ret;

		ret = kgdb_nmi_poll_one_knock();
		if (ret == NO_POLL_CHAR)
			return false;
		else if (ret == 1)
			break;
	}
	return true;
}