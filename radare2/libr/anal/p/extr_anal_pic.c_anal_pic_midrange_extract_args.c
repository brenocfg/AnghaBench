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
typedef  int ut16 ;
struct TYPE_4__ {int f; int d; int n; int k; int b; int m; } ;
typedef  TYPE_1__ PicMidrangeOpArgsVal ;
typedef  int PicMidrangeOpArgs ;

/* Variables and functions */
#define  PIC_MIDRANGE_OP_ARGS_11K 138 
 int PIC_MIDRANGE_OP_ARGS_11K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_1D_7F 137 
 int PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_D ; 
 int PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_1N_2M 136 
 int PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_M ; 
 int PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_N ; 
#define  PIC_MIDRANGE_OP_ARGS_1N_6K 135 
 int PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_K ; 
 int PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_N ; 
#define  PIC_MIDRANGE_OP_ARGS_2F 134 
 int PIC_MIDRANGE_OP_ARGS_2F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_3B_7F 133 
 int PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_B ; 
 int PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_4K 132 
 int PIC_MIDRANGE_OP_ARGS_4K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_7F 131 
 int PIC_MIDRANGE_OP_ARGS_7F_MASK_F ; 
#define  PIC_MIDRANGE_OP_ARGS_8K 130 
 int PIC_MIDRANGE_OP_ARGS_8K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_9K 129 
 int PIC_MIDRANGE_OP_ARGS_9K_MASK_K ; 
#define  PIC_MIDRANGE_OP_ARGS_NONE 128 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void anal_pic_midrange_extract_args (ut16 instr,
					    PicMidrangeOpArgs args,
					    PicMidrangeOpArgsVal *args_val) {

	memset (args_val, 0, sizeof (PicMidrangeOpArgsVal));

	switch (args) {
	case PIC_MIDRANGE_OP_ARGS_NONE: return;
	case PIC_MIDRANGE_OP_ARGS_2F:
		args_val->f = instr & PIC_MIDRANGE_OP_ARGS_2F_MASK_F;
		return;
	case PIC_MIDRANGE_OP_ARGS_7F:
		args_val->f = instr & PIC_MIDRANGE_OP_ARGS_7F_MASK_F;
		return;
	case PIC_MIDRANGE_OP_ARGS_1D_7F:
		args_val->f = instr & PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_F;
		args_val->d =
			(instr & PIC_MIDRANGE_OP_ARGS_1D_7F_MASK_D) >> 7;
		return;
	case PIC_MIDRANGE_OP_ARGS_1N_6K:
		args_val->n =
			(instr & PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_N) >> 6;
		args_val->k = instr & PIC_MIDRANGE_OP_ARGS_1N_6K_MASK_K;
		return;
	case PIC_MIDRANGE_OP_ARGS_3B_7F:
		args_val->b =
			(instr & PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_B) >> 7;
		args_val->f = instr & PIC_MIDRANGE_OP_ARGS_3B_7F_MASK_F;
		return;
	case PIC_MIDRANGE_OP_ARGS_4K:
		args_val->k = instr & PIC_MIDRANGE_OP_ARGS_4K_MASK_K;
		return;
	case PIC_MIDRANGE_OP_ARGS_8K:
		args_val->k = instr & PIC_MIDRANGE_OP_ARGS_8K_MASK_K;
		return;
	case PIC_MIDRANGE_OP_ARGS_9K:
		args_val->k = instr & PIC_MIDRANGE_OP_ARGS_9K_MASK_K;
		return;
	case PIC_MIDRANGE_OP_ARGS_11K:
		args_val->k = instr & PIC_MIDRANGE_OP_ARGS_11K_MASK_K;
		return;
	case PIC_MIDRANGE_OP_ARGS_1N_2M:
		args_val->n =
			(instr & PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_N) >> 2;
		args_val->m = instr & PIC_MIDRANGE_OP_ARGS_1N_2M_MASK_M;
		return;
	}
}