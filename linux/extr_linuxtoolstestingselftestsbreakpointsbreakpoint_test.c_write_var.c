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
 int /*<<< orphan*/  check_trapped () ; 
 int /*<<< orphan*/ * dummy_var ; 

__attribute__((used)) static void write_var(int len)
{
	char *pcval; short *psval; int *pival; long long *plval;
	int i;

	for (i = 0; i < 4; i++) {
		switch (len) {
		case 1:
			pcval = (char *)&dummy_var[i];
			*pcval = 0xff;
			break;
		case 2:
			psval = (short *)&dummy_var[i];
			*psval = 0xffff;
			break;
		case 4:
			pival = (int *)&dummy_var[i];
			*pival = 0xffffffff;
			break;
		case 8:
			plval = (long long *)&dummy_var[i];
			*plval = 0xffffffffffffffffLL;
			break;
		}
		check_trapped();
	}
}