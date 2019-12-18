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

char *get_reg_name_3(ut32 idx) {
	char *res = NULL;

	switch (idx) {
	case 0: res = "ac0"; break;
	case 1: res = "ac1"; break;
	case 2: res = "ac2"; break;
	case 3: res = "ac3"; break;
	case 4: res = "ac4"; break;
	case 5: res = "ac5"; break;
	case 6: res = "ac6"; break;
	case 7: res = "ac7"; break;
	case 8: res = "ac8"; break;
	case 9: res = "ac9"; break;
	case 10: res = "ac10"; break;
	case 11: res = "ac11"; break;
	case 12: res = "ac12"; break;
	case 13: res = "ac13"; break;
	case 14: res = "ac14"; break;
	case 15: res = "ac15"; break;
	case 16: res = "ac16"; break;
	case 17: res = "ac17"; break;
	case 18: res = "ac18"; break;
	case 19: res = "ac19"; break;
	case 20: res = "ac20"; break;
	case 21: res = "ac21"; break;
	case 22: res = "ac22"; break;
	case 23: res = "ac23"; break;
	case 24: res = "ac24"; break;
	case 25: res = "ac25"; break;
	case 26: res = "ac26"; break;
	case 27: res = "ac27"; break;
	case 28: res = "ac28"; break;
	case 29: res = "ac29"; break;
	case 30: res = "ac30"; break;
	case 31: res = "ac31"; break;
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