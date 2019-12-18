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
typedef  int /*<<< orphan*/  ut16 ;
struct cr16_cmd {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  CR16_ADD 140 
#define  CR16_ADDU 139 
#define  CR16_AND 138 
#define  CR16_ASHU 137 
#define  CR16_BITI 136 
#define  CR16_CMP 135 
#define  CR16_LSH 134 
#define  CR16_MOV 133 
#define  CR16_MUL 132 
#define  CR16_OR 131 
#define  CR16_SUB 130 
#define  CR16_SUBC 129 
 int /*<<< orphan*/  CR16_TYPE_ADD ; 
 int /*<<< orphan*/  CR16_TYPE_AND ; 
 int /*<<< orphan*/  CR16_TYPE_BIT ; 
 int /*<<< orphan*/  CR16_TYPE_CMP ; 
 int /*<<< orphan*/  CR16_TYPE_MOV ; 
 int /*<<< orphan*/  CR16_TYPE_MUL ; 
 int /*<<< orphan*/  CR16_TYPE_OR ; 
 int /*<<< orphan*/  CR16_TYPE_SHIFT ; 
 int /*<<< orphan*/  CR16_TYPE_SUB ; 
 int /*<<< orphan*/  CR16_TYPE_XOR ; 
#define  CR16_XOR 128 
 int cr16_get_opcode_low (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void cr16_anal_4bit_opcode(const ut16 in, struct cr16_cmd *cmd)
{
	switch (cr16_get_opcode_low(in)) {
	case CR16_ADDU:
	case CR16_ADD:
		cmd->type = CR16_TYPE_ADD;
		break;
	case CR16_BITI:
		cmd->type = CR16_TYPE_BIT;
		break;
	case CR16_MUL:
		cmd->type = CR16_TYPE_MUL;
		break;
	case CR16_SUBC:
	case CR16_SUB:
		cmd->type = CR16_TYPE_SUB;
		break;
	case CR16_CMP:
		cmd->type = CR16_TYPE_CMP;
		break;
	case CR16_XOR:
		cmd->type = CR16_TYPE_XOR;
		break;
	case CR16_OR:
		cmd->type = CR16_TYPE_OR;
		break;
	case CR16_ASHU:
	case CR16_LSH:
		cmd->type = CR16_TYPE_SHIFT;
		break;
	case CR16_MOV:
		cmd->type = CR16_TYPE_MOV;
		break;
	case CR16_AND:
		cmd->type = CR16_TYPE_AND;
		break;
	}
}