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

__attribute__((used)) static void read_var(int len)
{
	char cval __attribute__((unused));
	short sval __attribute__((unused));
	int ival __attribute__((unused));
	long long lval __attribute__((unused));

	switch (len) {
	case 1:
		cval = *(char *)dummy_var;
		break;
	case 2:
		sval = *(short *)dummy_var;
		break;
	case 4:
		ival = *(int *)dummy_var;
		break;
	case 8:
		lval = *(long long *)dummy_var;
		break;
	}
}