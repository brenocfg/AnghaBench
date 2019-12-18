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
 scalar_t__ dummy_var ; 

__attribute__((used)) static void write_var(int len)
{
	long long *plval;
	char *pcval;
	short *psval;
	int *pival;

	switch (len) {
	case 1:
		pcval = (char *)dummy_var;
		*pcval = 0xff;
		break;
	case 2:
		psval = (short *)dummy_var;
		*psval = 0xffff;
		break;
	case 4:
		pival = (int *)dummy_var;
		*pival = 0xffffffff;
		break;
	case 8:
		plval = (long long *)dummy_var;
		*plval = 0xffffffffffffffffLL;
		break;
	}
}