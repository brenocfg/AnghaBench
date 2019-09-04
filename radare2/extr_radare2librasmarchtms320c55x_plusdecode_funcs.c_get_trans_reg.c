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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 

char *get_trans_reg(ut32 ins_bits) {
	char *res = NULL;

	switch (ins_bits) {
	case 6:
		res = "trn0";
		break;
	case 7:
		res = "trn1";
		break;
	case 4:
		res = "trn2";
		break;
	case 5:
		res = "trn3";
		break;
	case 2:
		res = "trn4";
		break;
	case 3:
		res = "trn5";
		break;
	case 0:
		res = "trn6";
		break;
	case 1:
		res = "trn7";
		break;

	default:
		fprintf (stderr, "Invalid transaction instruction 0x%x\n", ins_bits);
	}
	return res? strdup (res): NULL;
}