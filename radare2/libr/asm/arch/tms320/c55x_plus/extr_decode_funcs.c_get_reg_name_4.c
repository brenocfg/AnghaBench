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

char *get_reg_name_4(ut32 idx) {
	char *res = NULL;

	switch (idx) {
	case 0:
		res = "ac0";
		break;
	case 1:
		res = "ac1";
		break;
	case 2:
		res = "ac2";
		break;
	case 3:
		res = "ac3";
		break;
	case 4:
		res = "ac4";
		break;
	case 5:
		res = "ac5";
		break;
	case 6:
		res = "ac6";
		break;
	case 7:
		res = "ac7";
		break;
	case 8:
		res = "t0";
		break;
	case 9:
		res = "t1";
		break;
	case 10:
		res = "t2";
		break;
	case 11:
		res = "t3";
		break;
	case 16:
		res = "ar0";
		break;
	case 17:
		res = "ar1";
		break;
	case 18:
		res = "ar2";
		break;
	case 19:
		res = "ar3";
		break;
	case 20:
		res = "ar4";
		break;
	case 21:
		res = "ar5";
		break;
	case 22:
		res = "ar6";
		break;
	case 23:
		res = "ar7";
		break;
	case 24:
		res = "ac0.l";
		break;
	case 25:
		res = "ac1.l";
		break;
	case 26:
		res = "ac2.l";
		break;
	case 27:
		res = "ac3.l";
		break;
	case 28:
		res = "ac4.l";
		break;
	case 29:
		res = "ac5.l";
		break;
	case 30:
		res = "ac6.l";
		break;
	case 31:
		res = "ac7.l";
		break;
	}
	return res? strdup (res): NULL;
}