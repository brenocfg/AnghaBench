#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t last_var; TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_12__ {size_t var; } ;
struct TYPE_11__ {size_t var; } ;
struct TYPE_14__ {int opcode; int op1_type; int op2_type; TYPE_2__ op2; TYPE_1__ op1; } ;
typedef  TYPE_4__ zend_op ;
typedef  int /*<<< orphan*/  (* zend_needs_live_range_cb ) (TYPE_3__*,TYPE_4__*) ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int IS_TMP_VAR ; 
 int IS_VAR ; 
#define  ZEND_ADD_ARRAY_ELEMENT 153 
#define  ZEND_ADD_ARRAY_UNPACK 152 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
#define  ZEND_BEGIN_SILENCE 151 
#define  ZEND_BOOL 150 
#define  ZEND_BOOL_NOT 149 
 int /*<<< orphan*/  ZEND_CALL_VAR_NUM (int /*<<< orphan*/ *,size_t) ; 
#define  ZEND_COPY_TMP 148 
#define  ZEND_DECLARE_ANON_CLASS 147 
 int ZEND_DO_FCALL ; 
#define  ZEND_DO_FCALL_BY_NAME 146 
#define  ZEND_DO_ICALL 145 
#define  ZEND_DO_UCALL 144 
#define  ZEND_FAST_CALL 143 
#define  ZEND_FETCH_CLASS 142 
#define  ZEND_FE_RESET_R 141 
#define  ZEND_FE_RESET_RW 140 
 int ZEND_FREE ; 
#define  ZEND_INIT_DYNAMIC_CALL 139 
#define  ZEND_INIT_FCALL 138 
#define  ZEND_INIT_FCALL_BY_NAME 137 
#define  ZEND_INIT_METHOD_CALL 136 
#define  ZEND_INIT_NS_FCALL_BY_NAME 135 
#define  ZEND_INIT_STATIC_METHOD_CALL 134 
#define  ZEND_INIT_USER_CALL 133 
#define  ZEND_JMPNZ_EX 132 
#define  ZEND_JMPZ_EX 131 
 size_t ZEND_LIVE_LOOP ; 
 size_t ZEND_LIVE_NEW ; 
 size_t ZEND_LIVE_ROPE ; 
 size_t ZEND_LIVE_SILENCE ; 
 size_t ZEND_LIVE_TMPVAR ; 
#define  ZEND_NEW 130 
#define  ZEND_ROPE_ADD 129 
#define  ZEND_ROPE_INIT 128 
 int /*<<< orphan*/  emit_live_range_raw (TYPE_3__*,size_t,size_t,size_t,size_t) ; 

__attribute__((used)) static void emit_live_range(
		zend_op_array *op_array, uint32_t var_num, uint32_t start, uint32_t end,
		zend_needs_live_range_cb needs_live_range) {
	zend_op *def_opline = &op_array->opcodes[start], *orig_def_opline = def_opline;
	zend_op *use_opline = &op_array->opcodes[end];
	uint32_t kind;

	switch (def_opline->opcode) {
		/* These should never be the first def. */
		case ZEND_ADD_ARRAY_ELEMENT:
		case ZEND_ADD_ARRAY_UNPACK:
		case ZEND_ROPE_ADD:
			ZEND_ASSERT(0);
			return;
		/* Result is boolean, it doesn't have to be destroyed. */
		case ZEND_JMPZ_EX:
		case ZEND_JMPNZ_EX:
		case ZEND_BOOL:
		case ZEND_BOOL_NOT:
		/* Classes don't have to be destroyed. */
		case ZEND_FETCH_CLASS:
		case ZEND_DECLARE_ANON_CLASS:
		/* FAST_CALLs don't have to be destroyed. */
		case ZEND_FAST_CALL:
			return;
		case ZEND_BEGIN_SILENCE:
			kind = ZEND_LIVE_SILENCE;
			start++;
			break;
		case ZEND_ROPE_INIT:
			kind = ZEND_LIVE_ROPE;
			/* ROPE live ranges include the generating opcode. */
			def_opline--;
			break;
		case ZEND_FE_RESET_R:
		case ZEND_FE_RESET_RW:
			kind = ZEND_LIVE_LOOP;
			start++;
			break;
		/* Objects created via ZEND_NEW are only fully initialized
		 * after the DO_FCALL (constructor call).
		 * We are creating two live-ranges: ZEND_LINE_NEW for uninitialized
		 * part, and ZEND_LIVE_TMPVAR for initialized.
		 */
		case ZEND_NEW:
		{
			int level = 0;
			uint32_t orig_start = start;

			while (def_opline + 1 < use_opline) {
				def_opline++;
				start++;
				if (def_opline->opcode == ZEND_DO_FCALL) {
					if (level == 0) {
						break;
					}
					level--;
				} else {
					switch (def_opline->opcode) {
						case ZEND_INIT_FCALL:
						case ZEND_INIT_FCALL_BY_NAME:
						case ZEND_INIT_NS_FCALL_BY_NAME:
						case ZEND_INIT_DYNAMIC_CALL:
						case ZEND_INIT_USER_CALL:
						case ZEND_INIT_METHOD_CALL:
						case ZEND_INIT_STATIC_METHOD_CALL:
						case ZEND_NEW:
							level++;
							break;
						case ZEND_DO_ICALL:
						case ZEND_DO_UCALL:
						case ZEND_DO_FCALL_BY_NAME:
							level--;
							break;
					}
				}
			}
			emit_live_range_raw(op_array, var_num, ZEND_LIVE_NEW, orig_start + 1, start + 1);
			if (start + 1 == end) {
				/* Trivial live-range, no need to store it. */
				return;
			}
			/* break missing intentionally */
		default:
			start++;
			kind = ZEND_LIVE_TMPVAR;

			/* Check hook to determine whether a live range is necessary,
			 * e.g. based on type info. */
			if (needs_live_range && !needs_live_range(op_array, orig_def_opline)) {
				return;
			}
			break;
		}
		case ZEND_COPY_TMP:
		{
			/* COPY_TMP has a split live-range: One from the definition until the use in
			 * "null" branch, and another from the start of the "non-null" branch to the
			 * FREE opcode. */
			uint32_t rt_var_num =
				(uint32_t) (intptr_t) ZEND_CALL_VAR_NUM(NULL, op_array->last_var + var_num);
			zend_op *block_start_op = use_opline;

			if (needs_live_range && !needs_live_range(op_array, orig_def_opline)) {
				return;
			}

			while ((block_start_op-1)->opcode == ZEND_FREE) {
				block_start_op--;
			}

			kind = ZEND_LIVE_TMPVAR;
			start = block_start_op - op_array->opcodes;
			if (start != end) {
				emit_live_range_raw(op_array, var_num, kind, start, end);
			}

			do {
				use_opline--;
			} while (!(
				((use_opline->op1_type & (IS_TMP_VAR|IS_VAR)) && use_opline->op1.var == rt_var_num) ||
				((use_opline->op2_type & (IS_TMP_VAR|IS_VAR)) && use_opline->op2.var == rt_var_num)
			));

			start = def_opline + 1 - op_array->opcodes;
			end = use_opline - op_array->opcodes;
			emit_live_range_raw(op_array, var_num, kind, start, end);
			return;
		}
	}

	emit_live_range_raw(op_array, var_num, kind, start, end);
}