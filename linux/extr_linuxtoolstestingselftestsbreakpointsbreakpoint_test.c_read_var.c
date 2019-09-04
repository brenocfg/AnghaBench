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

__attribute__((used)) static void read_var(int len)
{
	char cval; short sval; int ival; long long lval;
	int i;

	for (i = 0; i < 4; i++) {
		switch (len) {
		case 1:
			cval = *(char *)&dummy_var[i];
			break;
		case 2:
			sval = *(short *)&dummy_var[i];
			break;
		case 4:
			ival = *(int *)&dummy_var[i];
			break;
		case 8:
			lval = *(long long *)&dummy_var[i];
			break;
		}
		check_trapped();
	}
}