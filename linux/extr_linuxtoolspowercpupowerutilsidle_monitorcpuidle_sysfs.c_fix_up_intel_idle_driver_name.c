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
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

void fix_up_intel_idle_driver_name(char *tmp, int num)
{
	/* fix up cpuidle name for intel idle driver */
	if (!strncmp(tmp, "NHM-", 4)) {
		switch (num) {
		case 1:
			strcpy(tmp, "C1");
			break;
		case 2:
			strcpy(tmp, "C3");
			break;
		case 3:
			strcpy(tmp, "C6");
			break;
		}
	} else if (!strncmp(tmp, "SNB-", 4)) {
		switch (num) {
		case 1:
			strcpy(tmp, "C1");
			break;
		case 2:
			strcpy(tmp, "C3");
			break;
		case 3:
			strcpy(tmp, "C6");
			break;
		case 4:
			strcpy(tmp, "C7");
			break;
		}
	} else if (!strncmp(tmp, "ATM-", 4)) {
		switch (num) {
		case 1:
			strcpy(tmp, "C1");
			break;
		case 2:
			strcpy(tmp, "C2");
			break;
		case 3:
			strcpy(tmp, "C4");
			break;
		case 4:
			strcpy(tmp, "C6");
			break;
		}
	}
}