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
typedef  int st32 ;

/* Variables and functions */
 int /*<<< orphan*/  check_arg (int,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* get_reg_name_1 (int) ; 
 char* get_reg_name_2 (int) ; 
 char* get_reg_name_3 (int) ; 
 int /*<<< orphan*/  r_str_ncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *decode_regis(char *reg_arg, st32 hash_code, ut32 ins_bits,
	ut32 *ret_ins_bits, int *err_code) {
	char reg_type;
	char *res;

	reg_type = *reg_arg;
	res = NULL;

	//printf("REG_TYPE %d %d\n", reg_type, ins_bits);

	switch (reg_type) {
		case 33:
			res = get_reg_name_1((ins_bits >> 1) |
					      ((ins_bits & 1) << 6));
			break;
		case 100:
			if (r_str_ncasecmp(reg_arg, "d(ALLx", 6)) {
				fprintf(stderr, "invalid register! %s\n", reg_arg);
				*err_code = -1;
				return NULL;
			}
			res = (check_arg(ins_bits, err_code) != 0 && *err_code == 0)? strdup("dbl(") : NULL;
			if (*err_code < 0) {
				return NULL;
			}
			break;
		case 41:
			if (r_str_ncasecmp(reg_arg, ")ALLx", 5)) {
				fprintf(stderr, "invalid register! %s\n", reg_arg);
				*err_code = -1;
				return NULL;
			}
			res = (check_arg(ins_bits, err_code) && *err_code == 0)? strdup(")") : NULL;
			if (*err_code < 0) {
				return NULL;
			}
			break;
		case 65:
			if (!r_str_ncasecmp(reg_arg, "ACLH", 4)) {
				res = get_reg_name_1(ins_bits + 64);
			} else if (!r_str_ncasecmp(reg_arg, "ACxP", 4)) {
				res = get_reg_name_1(ins_bits + 1);
			} else if (!r_str_ncasecmp(reg_arg, "ACx", 3) ||
				  !r_str_ncasecmp(reg_arg, "ADR", 3) ||
				  !r_str_ncasecmp(reg_arg, "ALL", 3) /* 430ADC */
				 ) {
				res = get_reg_name_1(ins_bits);
			}
			if (hash_code == 0xDF || hash_code == 0xE0) {
				*ret_ins_bits = ins_bits;
			}
			break;
		case 68:
			res = get_reg_name_1(ins_bits + 32);
			break;
		case 77:
			if (!r_str_ncasecmp(reg_arg, "MA", 2) || !r_str_ncasecmp(reg_arg, "MR", 2)) {
				res = get_reg_name_1(ins_bits);
			} else {
				res = get_reg_name_2(ins_bits);
			}
			break;
		case 83:
			res = get_reg_name_1(ins_bits);
			break;
		case 82:
			if (!r_str_ncasecmp(reg_arg, "RA", 2) || !r_str_ncasecmp(reg_arg, "RL", 2)) {
				res = get_reg_name_1(ins_bits);
			} else if (!r_str_ncasecmp(reg_arg, "RLP", 3) || !r_str_ncasecmp(reg_arg, "RxP", 3)) {
				res = get_reg_name_1(ins_bits + 1);
			} else if (!r_str_ncasecmp(reg_arg, "RX", 2)) {
				res = get_reg_name_1(ins_bits);
			} else {
				res = get_reg_name_2(ins_bits);
			}
			break;
		case 84:
			res = get_reg_name_1(ins_bits + 48);
			break;
		case 87:
			if (!r_str_ncasecmp(reg_arg, "WD", 2)) {
				res = get_reg_name_2(ins_bits);
			} else if (!r_str_ncasecmp(reg_arg, "WA", 2)) {
				res = get_reg_name_1(ins_bits);
			} else {
				res = NULL;
			}
			break;
		case 88:
			if (!r_str_ncasecmp(reg_arg, "XR", 2)) {
				res = get_reg_name_3(ins_bits);
			} else if (!r_str_ncasecmp(reg_arg, "XD", 2)) {
				res = get_reg_name_2(ins_bits + 32);
			} else {
				res = NULL;
			}
			break;
		default:
			res = NULL;
			break;
	}

	return res;
}