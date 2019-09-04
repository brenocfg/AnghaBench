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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */
 scalar_t__ C55PLUS_DEBUG ; 
 char* decode_regis (char*,int,int,int*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* get_AR_regs_class1 (int) ; 
 char* get_AR_regs_class2 (int,int*,int,int) ; 
 char* get_cmp_op (int) ; 
 int get_ins_bits (int,int,char*,int,int,int*) ; 
 char* get_opers (int) ; 
 char* get_reg_pair (int) ; 
 char* get_sim_reg (char*,int) ; 
 char* get_status_regs_and_bits (char*,int) ; 
 char* get_tc2_tc1 (int) ; 
 char* get_trans_reg (int) ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  is_linear_circular (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  r_str_ncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 char* strcat_dup (char*,char*,int) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char* get_token_decoded(st32 hash_code, char *ins_token, ut32 ins_token_len,
	char *reg_arg, ut32 *ret_ins_bits, ut32 *ret_reg_len, ut32 magic_value,
	ut32 ins_pos, ut32 ins_len, ut8 two_ins, int *err_code) {
	ut32 tok_op, ins_bits;
	char *res = NULL;
	char buff_aux[512];
	char *aux = NULL;
	ut32 ret_len = 0, flag;

	*ret_ins_bits = 0;
	*ret_reg_len = 0;

	ins_bits = get_ins_bits(hash_code, ins_pos, ins_token, ins_token_len, magic_value, err_code);
	if (*err_code < 0) {
		return NULL;
	}
	tok_op = *ins_token - 0x23;

	if (C55PLUS_DEBUG) {
		printf("WAY ins_bits: OP = %d 0x%x %s %d %d\n", tok_op, ins_bits, ins_token, ins_token_len, ins_pos);
		getchar();
	}

	switch (tok_op) {
	case 30:
	case 31:
	case 32:
	case 33:
	case 43:
	case 62:
	case 63:
	case 64:
	case 65:
		if (!reg_arg || *reg_arg == '\0') {
			res = strdup("<register>");
			goto ret_decode;
		}
		res = decode_regis(reg_arg, hash_code, ins_bits, ret_ins_bits, err_code);
		if (*err_code < 0) {
			return NULL;
		}
		break;
	case 35: res = ins_bits? strdup(" || far()") : NULL; break;
	case 36: res = ins_bits? strdup(" || local()") : NULL; break;
	case 37: res = get_opers(ins_bits); break;
	case 38:
		res = ins_bits? "lo" : "hi";
		res = strdup(res);
		break;
	case 39: res = get_cmp_op(ins_bits); break;
	case 40:
	case 48:
		sprintf(buff_aux, "#0x%x", (ins_bits << (32 - ins_token_len) >> (32 - ins_token_len)));
		res = strdup(buff_aux);
		break;
	case 70:
	case 72:
	case 80:
		if (reg_arg) {
			if (*reg_arg == '!') {
				res = get_reg_pair(ins_bits);
				break;
			} else if (!r_str_ncasecmp(reg_arg, "ST", 2)) {
				res = get_status_regs_and_bits(reg_arg, ins_bits);
				break;
			}
		}
		if (hash_code == 0xDF || hash_code == 0xE0) {
			*ret_ins_bits = ins_bits;
		}
		if (!reg_arg || *reg_arg != '-') {
			sprintf(buff_aux, "#0x%lx", (long unsigned int)ins_bits);
		} else {
			sprintf(buff_aux, "-#0x%lx", (long unsigned int)ins_bits);
		}
		res = strdup(buff_aux);
		if (!reg_arg || *reg_arg != 'm') {
			break;
		}

		res = strcat_dup(res, ")", 1);
		res = strcat_dup("*(", res, 2);

		if (magic_value & 0xC0) {
			res = strcat_dup(res, ")", 1);
			res = strcat_dup("volatile(", res, 2);
		} else if (magic_value & 0x30) {
			res = strcat_dup(res, ")", 1);
			res = strcat_dup("port(", res, 2);
		}
		break;
	case 41:
	case 73:
		if ((reg_arg && *reg_arg == 'L') || hash_code == 105 || hash_code == 7) {
			if (C55PLUS_DEBUG) {
				fprintf (stderr, "Ooops!!! look up address in sections!! %d", hash_code);
			}
		}
		if (reg_arg && *reg_arg == 'L') {
			ins_bits = ins_bits << (32 - ins_token_len) >> (32 - ins_token_len);
		}
		if (reg_arg && *reg_arg == 'i') {
			res = strdup ("");
		} else {
			sprintf(buff_aux, "#0x%06lx", (long unsigned int)ins_bits);
			res = strdup(buff_aux);
		}
		break;
	case 42:
		flag = 0;
		if (reg_arg && *reg_arg == '3') {
			flag = ins_bits & 1;
			ins_bits = ins_bits >> 1;
			reg_arg++;
		}
		if (magic_value & 1) {
			aux = get_sim_reg(reg_arg, ins_bits);
		} else if (reg_arg) {
			switch (*reg_arg) {
			case 'b':
			case 'd':
				reg_arg++;
				break;
			case '!':
				//strncpy(buff_aux, reg_arg + 1, 8);
				reg_arg+=10;
				//ins_bits2 = get_ins_bits(hash_code, ins_pos, buff_aux, 8);
				break;
			}
			aux = get_AR_regs_class2(ins_bits, &ret_len, ins_len + ins_pos, 1);
		}
		if (magic_value & 1) {
			aux = strcat_dup(aux, ")", 1);
			aux = strcat_dup("mmap(", aux, 2);
		} else if ((magic_value & 4) && is_linear_circular(ins_bits)) {
			aux = strcat_dup(aux, ")", 1);
			aux = strcat_dup("linear(", aux, 2);
		} else if ((magic_value & 8) && is_linear_circular(ins_bits)) {
			aux = strcat_dup(aux, ")", 1);
			aux = strcat_dup("circular(", aux, 2);
		} else if (magic_value & 2) {
			aux = strcat_dup(aux, ")", 1);
			aux = strcat_dup("lock(", aux, 2);
		} else if (reg_arg) {
			if (((magic_value & 0x10) && strchr(reg_arg, 'r')) ||
			   ((magic_value & 0x20) && strchr(reg_arg, 'w'))) {

				aux = strcat_dup(aux, ")", 1);
				aux = strcat_dup("port(", aux, 2);
			} else if (
			((magic_value & 0x40) && strchr(reg_arg, 'r')) ||
			((magic_value & 0x80000000) && strchr(reg_arg, 'w'))) {

				aux = strcat_dup(aux, ")", 1);
				aux = strcat_dup("volatile(", aux, 2);
			}
		}

		if (flag) {
			res = strcat_dup("t3 = ", aux, 2);
		} else {
			res = aux;
			*ret_reg_len = ret_len;
		}
		break;
	case 79:
		res = get_trans_reg(ins_bits);
		if (!res) {
			*err_code = -1;
		}
		break;
	case 49:
		if (reg_arg) {
			if (*reg_arg == '1') {
				res = get_tc2_tc1(ins_bits >> 1);
			} else if (*reg_arg == '2') {
				res = get_tc2_tc1 (ins_bits & 1);
			}
		} else {
			res = get_tc2_tc1 (ins_bits);
		}
		if (!res) {
			*err_code = -1;
			return NULL;
		}
		break;
	case 52:
		if (ins_bits == 0) {
			break;
		}
		if (reg_arg) {
			if (*reg_arg == 'H') {
				res = "hi(";
			} else if (*reg_arg == 'L') {
				res = "lo(";
			} else if (*reg_arg == 'd') {
				res = "dbl(";
			} else if (*reg_arg == ')') {
				res = ")";
			} else {
				res = "<W>";
			}
		} else {
			res = "<W !flags>";
		}
		res = strdup(res);
		break;
	case 53:
	case 54:
	case 55:
		flag = 0;
		if (reg_arg && *reg_arg == '3') {
			flag = ins_bits & 1;
			ins_bits = ins_bits >> 1;
			reg_arg++;
		}
		aux = get_AR_regs_class1(ins_bits);
		tok_op = ins_bits & 0xF;
		if (magic_value & 4) {
			if (tok_op <= 7 || tok_op == 0xF) {
				aux = strcat_dup(aux, ")", 1);
				aux = strcat_dup("linear(", aux, 2);
			}
		} else if (magic_value & 8) {
			if (tok_op <= 7 || tok_op == 0xF) {
				aux = strcat_dup(aux, ")", 1);
				aux = strcat_dup("circular(", aux, 2);
			}
		} else if (magic_value & 2) {
			aux = strcat_dup(aux, ")", 1);
			aux = strcat_dup("lock(", aux, 2);
		} else if (reg_arg) {
			if (
			   ((magic_value & 0x10) && *ins_token == 'X' && strchr(reg_arg, 'r'))
			    ||
			   ((magic_value & 0x20) && *ins_token == 'Y' && strchr(reg_arg, 'w'))
			  ) {

				aux = strcat_dup(aux, ")", 1);
				aux = strcat_dup("port(", aux, 2);
			} else if (
			((magic_value & 0x40) && *ins_token == 'X' && strchr(reg_arg, 'r'))
			    ||
			   ((magic_value & 0x80000000) && *ins_token == 'Y' && strchr(reg_arg, 'w'))

			) {
				aux = strcat_dup(aux, ")", 1);
				aux = strcat_dup("volatile(", aux, 2);
			}
		}
		res = flag? strcat_dup ("t3 = ", aux, 2): aux;
		break;
	case 0:
	case 1:
		if (!ins_bits) {
			break;
		}
		if (!reg_arg) {
			res = "U";
		} else {
			if (*reg_arg == '(') {
				res = "uns(";
			} else if (*reg_arg == ')') {
				res = ")";
			} else {
				res = "<$/#>";
			}
		}
		res = strdup(res);
		break;
	case 2:
		if (!ins_bits) {
			break;
		}
		if (!reg_arg) {
			res = "R";
		} else {
			if (*reg_arg == '(') {
				res = "rnd(";
			} else if (*reg_arg == ')') {
				res = ")";
			} else {
				res = "<%>";
			}
		}
		res = strdup(res);
		break;
	case 12:
		if (!ins_bits) {
			break;
		}
		if(!reg_arg) {
			res = "F";
		} else {
			if (*reg_arg == '(') {
				res = "frct(";
			} else if (*reg_arg == ')') {
				res = ")";
			} else if (*reg_arg == 'a') {
				res = "<%>";
			} else {
				res = "</>";
			}
		}
		res = strdup(res);
		break;
	case 29:
		if (!ins_bits) {
			break;
		}
		if (!reg_arg) {
			res = "saturate";
		} else {
			if (*reg_arg == '(')  {
				res = "saturate(";
			} else if (*reg_arg == ')') {
				res = ")";
			} else {
				res = "<saturate>";
			}
		}
		res = strdup(res);
		break;
	case 16:
		res = (ins_bits != 0)? strdup("t3 = ") : NULL;
		break;
	case 17:
		if (!ins_bits) {
			break;
		}
		if (!reg_arg) {
			res = "40";
		} else {
			if (*reg_arg == '(') {
				res = "m40(";
			} else if (*reg_arg == ')') {
				res = ")";
			} else {
				res = "<4>";
			}
		}
		res = strdup(res);
		break;
	case 78:
		if (!r_str_ncasecmp (ins_token, "q_SAT", 5)) {
			res = ins_bits? "s": NULL;
		} else if (!r_str_ncasecmp(ins_token, "q_CIRC", 6)) {
			res = ins_bits? ".cr": NULL;
		} else if (!r_str_ncasecmp(ins_token, "q_LINR", 6)) {
			res = ins_bits? ".lr": NULL;
		} else {
			fprintf (stderr, "Invalid instruction %s\n!", ins_token);
			*err_code = -1;
			return NULL;
		}
		if (res != NULL) {
			if (C55PLUS_DEBUG) {
				printf("OP(78): TOKEN=%s\n", res);
			}
			res = strdup(res);
		}
		break;
	}

ret_decode:
	if (C55PLUS_DEBUG) {
		printf ("RES = %s\n", (res) ? res :"NULL");
	}
	return res;
}