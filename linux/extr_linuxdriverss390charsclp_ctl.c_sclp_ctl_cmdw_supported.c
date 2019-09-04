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
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* sclp_ctl_sccb_wlist ; 

__attribute__((used)) static int sclp_ctl_cmdw_supported(unsigned int cmdw)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(sclp_ctl_sccb_wlist); i++) {
		if (cmdw == sclp_ctl_sccb_wlist[i])
			return 1;
	}
	return 0;
}