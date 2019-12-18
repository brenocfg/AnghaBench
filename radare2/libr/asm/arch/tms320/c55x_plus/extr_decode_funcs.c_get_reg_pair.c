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

char *get_reg_pair(ut32 idx) {
	char *res = NULL;

	switch (idx) {
	case 1: res = "ac0, ac2"; break;
	case 2: res = "ac1, ac3"; break;
	case 3: res = "pair(ac0), pair(ac2)"; break;
	case 4: res = "ar0, ar1"; break;
	case 5: res = "ar0, ar2"; break;
	case 6: res = "ar1, ar3"; break;
	case 7: res = "pair(ar0), pair(ar2)"; break;
	case 9: res = "t0, t2"; break;
	case 10: res = "t1, t3"; break;
	case 11: res = "pair(t0), pair(t2)"; break;
	case 21: res = "ar4, t0"; break;
	case 22: res = "ar5, t1"; break;
	case 23: res = "pair(ar4), pair(t0)"; break;
	case 25: res = "ar6, t2"; break;
	case 26: res = "ar7, t3"; break;
	case 27: res = "pair(ar6), pair(t2)"; break;
	case 31: res = "block(ar4), block(t0)"; break;
	default: res = NULL;
	}

	if (res != NULL) {
		res = strdup (res);
	}

	return res;
}