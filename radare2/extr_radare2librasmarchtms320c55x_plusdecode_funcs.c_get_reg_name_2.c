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
typedef  int ut32 ;

/* Variables and functions */
 char* strdup (char*) ; 

char *get_reg_name_2(ut32 idx) {
	char *res = NULL;

	switch (idx) {
	case 0: res = "ar0"; break;
	case 1: res = "ar1"; break;
	case 2: res = "ar2"; break;
	case 3: res = "ar3"; break;
	case 4: res = "ar4"; break;
	case 5: res = "ar5"; break;
	case 6: res = "ar6"; break;
	case 7: res = "ar7"; break;
	case 8: res = "ar8"; break;
	case 9: res = "ar9"; break;
	case 10: res = "ar10"; break;
	case 11: res = "ar11"; break;
	case 12: res = "ar12"; break;
	case 13: res = "ar13"; break;
	case 14: res = "ar14"; break;
	case 15: res = "ar15"; break;
	case 16: res = "t0"; break;
	case 17: res = "t1"; break;
	case 18: res = "t2"; break;
	case 19: res = "t3"; break;
	case 20: res = "ssp"; break;
	case 21: res = "sp"; break;
	case 22: res = "dp"; break;
	case 32: res = "xar0"; break;
	case 33: res = "xar1"; break;
	case 34: res = "xar2"; break;
	case 35: res = "xar3"; break;
	case 36: res = "xar4"; break;
	case 37: res = "xar5"; break;
	case 38: res = "xar6"; break;
	case 39: res = "xar7"; break;
	case 40: res = "xar8"; break;
	case 41: res = "xar9"; break;
	case 42: res = "xar10"; break;
	case 43: res = "xar11"; break;
	case 44: res = "xar12"; break;
	case 45: res = "xar13"; break;
	case 46: res = "xar14"; break;
	case 47: res = "xar15"; break;
	case 52: res = "xssp"; break;
	case 53: res = "xsp"; break;
	case 54: res = "xdp"; break;
	default: res = NULL;
	}

	if (res != NULL) {
		res = strdup (res);
	}

	return res;
}