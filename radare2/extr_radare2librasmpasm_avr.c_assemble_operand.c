#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ RAsm ;

/* Variables and functions */
#define  OPERAND_BIT 150 
#define  OPERAND_BRANCH_ADDRESS 149 
#define  OPERAND_COMPLEMENTED_DATA 148 
#define  OPERAND_DATA 147 
#define  OPERAND_DES_ROUND 146 
#define  OPERAND_IO_REGISTER 145 
#define  OPERAND_LONG_ABSOLUTE_ADDRESS 144 
#define  OPERAND_MX 143 
#define  OPERAND_MY 142 
#define  OPERAND_MZ 141 
#define  OPERAND_REGISTER 140 
#define  OPERAND_REGISTER_EVEN_PAIR 139 
#define  OPERAND_REGISTER_EVEN_PAIR_STARTR24 138 
#define  OPERAND_REGISTER_STARTR16 137 
#define  OPERAND_RELATIVE_ADDRESS 136 
#define  OPERAND_X 135 
#define  OPERAND_XP 134 
#define  OPERAND_Y 133 
#define  OPERAND_YP 132 
#define  OPERAND_YPQ 131 
#define  OPERAND_Z 130 
#define  OPERAND_ZP 129 
#define  OPERAND_ZPQ 128 
 int getnum (TYPE_1__*,char const*) ; 
 int parse_registerpair (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int assemble_operand(RAsm *a, const char *operand, int type, uint32_t *res) {
	int ret = -1;
	int temp;

	switch (type) {
	case OPERAND_REGISTER_EVEN_PAIR:
		*res = parse_registerpair(operand);
		if (*res > 0) {
			ret = 0;
		}
		break;
	case OPERAND_REGISTER_EVEN_PAIR_STARTR24:
		*res = parse_registerpair(operand);
		// encoding in 2 bits for r25:r24 and upper pairs
		if (*res >= 12) {
			*res -= 12;
			ret = 0;
		}
		break;
	case OPERAND_BRANCH_ADDRESS:
	case OPERAND_RELATIVE_ADDRESS: // TODO: <-- check for negative (should be correct, but...)
		temp = getnum (a, operand); // return pure number
		/* the argument could be:
		- target address (will be calculated in according to current pc of assemble), ex: 0x4, 200, 0x1000
		or
		- relative address, ex: +2, -1, +60, -49 */
		if(a->pc || (operand[0] != '+' && operand[0] != '-')) { // for series of commands
			/* +2 from documentation:
			If Rd != Rr (Z = 0) then PC <- PC + k + 1, else PC <- PC + 1 */
			temp -= a->pc + 2;
		}
		temp /= 2; // in WORDs
		if (temp >= -64 && temp <= 63) {
			ret = 0;
		}
		*res = temp;
		break;
	case OPERAND_IO_REGISTER:
	case OPERAND_BIT:
	case OPERAND_DES_ROUND:
	case OPERAND_LONG_ABSOLUTE_ADDRESS:
	case OPERAND_DATA:
		*res = getnum(a, operand); // return pure number
		ret = 0;
		break;
	case OPERAND_COMPLEMENTED_DATA:
		*res = getnum(a, operand); // return pure number
		*res = ~(*res) & 0xFF; // complement it
		ret = 0;
		break;
	case OPERAND_MX:
	case OPERAND_X:
	case OPERAND_XP:
	case OPERAND_MY:
	case OPERAND_Y:
	case OPERAND_YP:
	case OPERAND_MZ:
	case OPERAND_Z:
	case OPERAND_ZP:
		*res = 0; //do nothing, operand is already encoded in opcode
		ret = 0;
		break;

	case OPERAND_YPQ:
	case OPERAND_ZPQ:
		if (strlen(operand) > 2) {
			/* return argument after '+' sign
			   we've already checked presence of '+' in parse_specialreg */
			*res = getnum(a, operand + 2);
			ret = 0;
		}
		break;

	case OPERAND_REGISTER:
		if (strlen(operand) > 1) {
			// returns register number (r__)
			*res = getnum(a, operand + 1);
			if (*res <= 32) {
				ret = 0;
			}
		}
		break;
	case OPERAND_REGISTER_STARTR16:
		if (strlen(operand) > 1) {
			// returns register number (r__)
			*res = getnum(a, operand + 1);
			if (*res >= 16 && *res <= 32) {
				*res -= 16;
				ret = 0;
			}
		}
		break;
	default:
		ret = -1;
	}

	return ret;
}