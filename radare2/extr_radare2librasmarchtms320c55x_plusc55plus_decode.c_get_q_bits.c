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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_str_ncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static ut32 get_q_bits(ut32 val, char *ins, ut32 ins_len, int *err_code) {
	ut32 res = 0;

	if (!r_str_ncasecmp(ins, "q_MMAP", 6)) {
		res = val & 1;
	} else if (!r_str_ncasecmp(ins, "q_LOCK", 6)) {
		res = val & 1;
	} else if (!r_str_ncasecmp(ins, "q_LINR", 6)) {
		res = (val >> 2) & 1;
	} else if (!r_str_ncasecmp(ins, "q_CIRC", 6)) {
		res = (val >> 3) & 1;
	} else if (!r_str_ncasecmp(ins, "q_PORT_READ", 11)) {
		res = (val >> 4) & 1;
	} else if (!r_str_ncasecmp(ins, "q_PORT_WRITE", 12)) {
		res = (val >> 5) & 1;
	} else if (!r_str_ncasecmp(ins, "q_XPORT_READ", 12)) {
		res = (val >> 6) & 1;
	} else if (!r_str_ncasecmp(ins, "q_XPORT_WRITE", 13)) {
		res = (val >> 7) & 1;
	} else if (!r_str_ncasecmp(ins, "q_SAT", 5)) {
		res = (val >> 8) & 1;
	} else if (!r_str_ncasecmp(ins, "q_XC0", 5)) {
		res = (val >> 9) & 1;
	} else if (!r_str_ncasecmp(ins, "q_XC1", 5)) {
		res = (val >> 10) & 1;
	} else {
		/* INVALID CONDITION */
		fprintf(stderr, "Invalid token %s\n", ins); *err_code = -1;
	}
	return res;
}