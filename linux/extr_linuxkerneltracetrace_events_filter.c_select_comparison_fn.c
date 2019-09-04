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
typedef  int /*<<< orphan*/ * filter_pred_fn_t ;
typedef  enum filter_op_ids { ____Placeholder_filter_op_ids } filter_op_ids ;

/* Variables and functions */
#define  OP_EQ 129 
#define  OP_NE 128 
 int PRED_FUNC_MAX ; 
 int PRED_FUNC_START ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/ * filter_pred_16 ; 
 int /*<<< orphan*/ * filter_pred_32 ; 
 int /*<<< orphan*/ * filter_pred_64 ; 
 int /*<<< orphan*/ * filter_pred_8 ; 
 int /*<<< orphan*/ ** pred_funcs_s16 ; 
 int /*<<< orphan*/ ** pred_funcs_s32 ; 
 int /*<<< orphan*/ ** pred_funcs_s64 ; 
 int /*<<< orphan*/ ** pred_funcs_s8 ; 
 int /*<<< orphan*/ ** pred_funcs_u16 ; 
 int /*<<< orphan*/ ** pred_funcs_u32 ; 
 int /*<<< orphan*/ ** pred_funcs_u64 ; 
 int /*<<< orphan*/ ** pred_funcs_u8 ; 

__attribute__((used)) static filter_pred_fn_t select_comparison_fn(enum filter_op_ids op,
					    int field_size, int field_is_signed)
{
	filter_pred_fn_t fn = NULL;
	int pred_func_index = -1;

	switch (op) {
	case OP_EQ:
	case OP_NE:
		break;
	default:
		if (WARN_ON_ONCE(op < PRED_FUNC_START))
			return NULL;
		pred_func_index = op - PRED_FUNC_START;
		if (WARN_ON_ONCE(pred_func_index > PRED_FUNC_MAX))
			return NULL;
	}

	switch (field_size) {
	case 8:
		if (pred_func_index < 0)
			fn = filter_pred_64;
		else if (field_is_signed)
			fn = pred_funcs_s64[pred_func_index];
		else
			fn = pred_funcs_u64[pred_func_index];
		break;
	case 4:
		if (pred_func_index < 0)
			fn = filter_pred_32;
		else if (field_is_signed)
			fn = pred_funcs_s32[pred_func_index];
		else
			fn = pred_funcs_u32[pred_func_index];
		break;
	case 2:
		if (pred_func_index < 0)
			fn = filter_pred_16;
		else if (field_is_signed)
			fn = pred_funcs_s16[pred_func_index];
		else
			fn = pred_funcs_u16[pred_func_index];
		break;
	case 1:
		if (pred_func_index < 0)
			fn = filter_pred_8;
		else if (field_is_signed)
			fn = pred_funcs_s8[pred_func_index];
		else
			fn = pred_funcs_u8[pred_func_index];
		break;
	}

	return fn;
}