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
typedef  int ut8 ;
typedef  int ut32 ;

/* Variables and functions */
 int get_ins_part (int,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,...) ; 

char *get_AR_regs_class2(ut32 ins_bits, ut32 *ret_len, ut32 ins_pos, ut32 idx) {
	ut8 op, op2, reg_num, type;
	char *res = NULL;

	op = ins_bits >> 6;
	op2 = ins_bits & 3;
	reg_num = (ins_bits >> 2) & 0xF;
	if (ret_len) {
		*ret_len = 0;
	}
	//printf("OP1 %x OP2 0x%x %x\n", op, op2, reg_num);
	res = malloc(50);
	if (!res) {
		return NULL;
	}	
	if(op2 == 2) {
		if(op) {
			sprintf (res, "*ar%ld(short(#0x%lx))",
				 (long int)reg_num, (long int)idx * op);
		} else {
			sprintf(res, "*ar%ld", (long int)reg_num);
		}
	} else {
		type = (op >> 3 | 2 * op2);
		if(type == 6) {
			sprintf(res, "@#0x%lx", (long int)idx * (reg_num | 16 * (op & 7)));
		} else if(type == 7) {
			sprintf(res, "*sp(#0x%lx)", (long int)idx * (reg_num | 16 * (op & 7)));
		} else {
			type = idx | 16 * op;
			switch(type) {
			case 0:
				sprintf(res, "*ar%ld-", (long int)reg_num);
				break;
			case 1:
				sprintf(res, "*ar%ld+", (long int)reg_num);
				break;
			case 2:
				sprintf(res, "*ar%ld(t0)", (long int)reg_num);
				break;
			case 3:
				sprintf(res, "*ar%ld(t1)", (long int)reg_num);
				break;
			case 4:
				sprintf(res, "*(ar%ld-t0)", (long int)reg_num);
				break;
			case 5:
				sprintf(res, "*(ar%ld-t1)", (long int)reg_num);
				break;
			case 6:
				sprintf(res, "*(ar%ld+t0)", (long int)reg_num);
				break;
			case 7:
				sprintf(res, "*(ar%ld+t1)", (long int)reg_num);
				break;
			case 8:
				sprintf(res, "*-ar%ld", (long int)reg_num);
				break;
			case 9:
				sprintf(res, "*+ar%ld", (long int)reg_num);
				break;
			case 10:
				sprintf(res, "*ar%ld(t2)", (long int)reg_num);
				break;
			case 11:
				sprintf(res, "*ar%ld(t3)", (long int)reg_num);
				break;
			case 12:
				sprintf(res, "*(ar%ld-t2)", (long int)reg_num);
				break;
			case 13:
				sprintf(res, "*(ar%ld-t3)", (long int)reg_num);
				break;
			case 14:
				sprintf(res, "*(ar%ld+t2)", (long int)reg_num);
				break;
			case 15:
				sprintf(res, "*(ar%ld+t3)", (long int)reg_num);
				break;
			case 16:
				sprintf(res, "*(ar%ld-t0b)", (long int)reg_num);
				break;
			case 17:
				sprintf(res, "*(ar%ld+t0b)", (long int)reg_num);
				break;
			case 18:
				sprintf(res, "*ar%ld(t0<<#1)", (long int)reg_num);
				break;
			case 19:
				sprintf(res, "*ar%ld(t1<<#1)", (long int)reg_num);
				break;
			case 23:
				sprintf(res, "*ar%ld(xar15)", (long int)reg_num);
				break;

			case 24:
			case 25:
			case 26:
			case 27:
				idx = get_ins_part(ins_pos, 2);
				if(ret_len) {
					*ret_len = 2;
				}
				switch (type) {
				case 24:
					sprintf(res, "*ar%ld(#%ld)", (long int)reg_num, (long int)op * idx);
					break;
				case 25:
					sprintf(res, "*+ar%ld(#%ld)", (long int)reg_num, (long int)op * idx);
					break;
				case 26:
					sprintf(res, "*abs16(#0x%lx)", (long int)idx);
					break;
				default:
					sprintf(res, "*port(#0x%lx)",  (long int)idx);
					break;
				}
				break;
			case 28:
			case 29:
			case 30:
				idx = get_ins_part(ins_pos, 3);
				if(ret_len) {
					*ret_len = 3;
				}
				switch (type) {
				case 28:
					sprintf(res, "*ar%ld(#0x%lx)", (long int)reg_num, (long int)idx * op);
					break;
				case 29:
					sprintf(res, "*+ar%ld(#0x%lx)", (long int)reg_num, (long int)idx * op);
					break;
				default:
					sprintf(res, "*(#0x%lx)", (long int)idx);
					break;
				}

				break;
			}
		}
	}

	return res;
}