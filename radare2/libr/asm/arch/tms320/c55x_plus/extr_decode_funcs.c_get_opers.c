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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* get_reg_name_1 (int /*<<< orphan*/ ) ; 
 char* get_reg_name_4 (int) ; 
 char* strcat_dup (char*,char*,int) ; 
 char* strdup (char*) ; 

char *get_opers(ut8 oper_byte) {
	char *res = NULL;
	ut8 oper_type = 0x00;
	char *reg_name = NULL;

	switch (oper_byte) {
	case 0xE0u:
		res = strdup ("overflow(ac0)");
		break;
	case 0xE1u:
		res = strdup ("overflow(ac1)");
		break;
	case 0xE2u:
		res = strdup ("overflow(ac2)");
		break;
	case 0xE3u:
		res = strdup ("overflow(ac3)");
		break;
	case 0xE4u:
		res = strdup ("tc1");
		break;
	case 0xE5u:
		res = strdup ("tc2");
		break;
	case 0xE6u:
		res = strdup ("carry");
		break;
	case 0xE7u:
		res = strdup ("overflow(govf)");
		break;
	case 0xE8u:
		res = strdup ("tc1 & tc2");
		break;
	case 0xE9u:
		res = strdup ("tc1 & !tc2");
		break;
	case 0xEAu:
		res = strdup ("!tc1 & tc2");
		break;
	case 0xEBu:
		res = strdup ("!tc1 & !tc2");
		break;
	case 0xECu:
		res = strdup ("word_mode");
		break;
	case 0xEDu:
		res = strdup ("byte_mode");
		break;
	case 0xF0u:
		res = strdup ("!overflow(ac0)");
		break;
	case 0xF1u:
		res = strdup ("!overflow(ac1)");
		break;
	case 0xF2u:
		res = strdup ("!overflow(ac2)");
		break;
	case 0xF3u:
		res = strdup ("!overflow(ac3)");
		break;
	case 0xF4u:
		res = strdup ("!tc1");
		break;
	case 0xF5u:
		res = strdup ("!tc2");
		break;
	case 0xF6u:
		res = strdup ("!carry");
		break;
	case 0xF7u:
		res = strdup ("!overflow(govf)");
		break;
	case 0xF8u:
		res = strdup ("tc1 | tc2");
		break;
	case 0xF9u:
		res = strdup ("tc1 | !tc2");
		break;
	case 0xFAu:
		res = strdup ("!tc1 | tc2");
		break;
	case 0xFBu:
		res = strdup ("!tc1 | !tc2");
		break;
	case 0xFCu:
		res = strdup ("tc1 ^ tc2");
		break;
	case 0xFDu:
		res = strdup ("tc1 ^ !tc2");
		break;
	case 0xFEu:
		res = strdup ("!tc1 ^ tc2");
		break;
	case 0xFFu:
		res = strdup("!tc1 ^ !tc2");
		break;
	default:
		oper_type = oper_byte >> 5;
		if (oper_type != 6 ) {
			reg_name = get_reg_name_4 (oper_byte & 0x1F);
			switch (oper_type) {
			case 1u:
				res = strcat_dup (reg_name, " != #0", 1);
				break;
			case 0u:
				res = strcat_dup (reg_name, " == #0", 1);
				break;
			case 2u:
				res =  strcat_dup (reg_name, " < #0", 1);
				break;
			case 3u:
				res =  strcat_dup (reg_name, " >= #0", 1);
				break;
			case 4u:
				res =  strcat_dup (reg_name, " > #0", 1);
				break;
			case 5u:
				res =  strcat_dup (reg_name, " <= #0", 1);
			}
			//TODO: still can leak
			return res;
		}
		reg_name = get_reg_name_1 ((oper_byte & 0xF) + 128);
		oper_type = (oper_byte >> 4) - 12;
		if (oper_type) {
			if (oper_type != 1) {
				free (reg_name);
				return NULL;
			}
			res = strcat_dup (reg_name, " != #0", 1);
		} else {
			// coverity may complain but strcat_dup set to null
			// reg_name when free
			res = strcat_dup (reg_name, " == #0", 1);
		}
	}
	free (reg_name);
	return res;
}