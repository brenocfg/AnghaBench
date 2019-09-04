#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int definition; int use_chain; int /*<<< orphan*/ * phi_use_chain; } ;
typedef  TYPE_4__ zend_ssa_var ;
struct TYPE_14__ {int result_def; } ;
typedef  TYPE_5__ zend_ssa_op ;
struct TYPE_12__ {int /*<<< orphan*/  var; } ;
struct TYPE_15__ {int opcode; TYPE_3__ result; int /*<<< orphan*/  result_type; } ;
typedef  TYPE_6__ zend_op ;
typedef  int zend_bool ;
struct TYPE_16__ {TYPE_2__* op_array; TYPE_1__* ssa; } ;
typedef  TYPE_7__ context ;
struct TYPE_11__ {TYPE_6__* opcodes; } ;
struct TYPE_10__ {TYPE_5__* ops; TYPE_4__* vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UNUSED ; 
#define  ZEND_ASSERT_CHECK 160 
#define  ZEND_ASSIGN 159 
#define  ZEND_ASSIGN_ADD 158 
#define  ZEND_ASSIGN_BW_AND 157 
#define  ZEND_ASSIGN_BW_OR 156 
#define  ZEND_ASSIGN_BW_XOR 155 
#define  ZEND_ASSIGN_CONCAT 154 
#define  ZEND_ASSIGN_DIM 153 
#define  ZEND_ASSIGN_DIV 152 
#define  ZEND_ASSIGN_MOD 151 
#define  ZEND_ASSIGN_MUL 150 
#define  ZEND_ASSIGN_OBJ 149 
#define  ZEND_ASSIGN_OBJ_REF 148 
#define  ZEND_ASSIGN_POW 147 
#define  ZEND_ASSIGN_REF 146 
#define  ZEND_ASSIGN_SL 145 
#define  ZEND_ASSIGN_SR 144 
#define  ZEND_ASSIGN_STATIC_PROP 143 
#define  ZEND_ASSIGN_STATIC_PROP_REF 142 
#define  ZEND_ASSIGN_SUB 141 
#define  ZEND_DO_FCALL 140 
#define  ZEND_DO_FCALL_BY_NAME 139 
#define  ZEND_DO_ICALL 138 
#define  ZEND_DO_UCALL 137 
#define  ZEND_INCLUDE_OR_EVAL 136 
#define  ZEND_POST_DEC_OBJ 135 
#define  ZEND_POST_INC_OBJ 134 
#define  ZEND_PRE_DEC 133 
#define  ZEND_PRE_DEC_OBJ 132 
#define  ZEND_PRE_INC 131 
#define  ZEND_PRE_INC_OBJ 130 
#define  ZEND_YIELD 129 
#define  ZEND_YIELD_FROM 128 

__attribute__((used)) static zend_bool try_remove_var_def(context *ctx, int free_var, int use_chain, zend_op *opline) {
	if (use_chain >= 0) {
		return 0;
	}
	zend_ssa_var *var = &ctx->ssa->vars[free_var];
	int def = var->definition;

	if (def >= 0) {
		zend_ssa_op *def_op = &ctx->ssa->ops[def];

		if (def_op->result_def == free_var
				&& var->phi_use_chain == NULL
				&& var->use_chain == (opline - ctx->op_array->opcodes)) {
			zend_op *def_opline = &ctx->op_array->opcodes[def];

			switch (def_opline->opcode) {
				case ZEND_ASSIGN:
				case ZEND_ASSIGN_REF:
				case ZEND_ASSIGN_DIM:
				case ZEND_ASSIGN_OBJ:
				case ZEND_ASSIGN_OBJ_REF:
				case ZEND_ASSIGN_STATIC_PROP:
				case ZEND_ASSIGN_STATIC_PROP_REF:
				case ZEND_ASSIGN_ADD:
				case ZEND_ASSIGN_SUB:
				case ZEND_ASSIGN_MUL:
				case ZEND_ASSIGN_DIV:
				case ZEND_ASSIGN_MOD:
				case ZEND_ASSIGN_SL:
				case ZEND_ASSIGN_SR:
				case ZEND_ASSIGN_CONCAT:
				case ZEND_ASSIGN_BW_OR:
				case ZEND_ASSIGN_BW_AND:
				case ZEND_ASSIGN_BW_XOR:
				case ZEND_ASSIGN_POW:
				case ZEND_PRE_INC:
				case ZEND_PRE_DEC:
				case ZEND_PRE_INC_OBJ:
				case ZEND_POST_INC_OBJ:
				case ZEND_PRE_DEC_OBJ:
				case ZEND_POST_DEC_OBJ:
				case ZEND_DO_ICALL:
				case ZEND_DO_UCALL:
				case ZEND_DO_FCALL_BY_NAME:
				case ZEND_DO_FCALL:
				case ZEND_INCLUDE_OR_EVAL:
				case ZEND_YIELD:
				case ZEND_YIELD_FROM:
				case ZEND_ASSERT_CHECK:
					def_opline->result_type = IS_UNUSED;
					def_opline->result.var = 0;
					def_op->result_def = -1;
					var->definition = -1;
					return 1;
				default:
					break;
			}
		}
	}
	return 0;
}