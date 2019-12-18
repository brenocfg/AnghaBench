#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
#define  ARM_CC_AL 142 
#define  ARM_CC_EQ 141 
#define  ARM_CC_GE 140 
#define  ARM_CC_GT 139 
#define  ARM_CC_HI 138 
#define  ARM_CC_HS 137 
#define  ARM_CC_LE 136 
#define  ARM_CC_LO 135 
#define  ARM_CC_LS 134 
#define  ARM_CC_LT 133 
#define  ARM_CC_MI 132 
#define  ARM_CC_NE 131 
#define  ARM_CC_PL 130 
#define  ARM_CC_VC 129 
#define  ARM_CC_VS 128 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*) ; 

const char* arm_prefix_cond(RAnalOp *op, int cond_type) {
	const char *close_cond[2];
	close_cond[0] = "\0";
	close_cond[1] = ",}\0";
	int close_type = 0;
	switch (cond_type) {
	case ARM_CC_EQ:
		close_type = 1;
		r_strbuf_setf (&op->esil, "zf,?{,");
		break;
	case ARM_CC_NE:
		close_type = 1;
		r_strbuf_setf (&op->esil, "zf,!,?{,");
		break;
	case ARM_CC_HS:
		close_type = 1;
		r_strbuf_setf (&op->esil, "cf,?{,");
		break;
	case ARM_CC_LO:
		close_type = 1;
		r_strbuf_setf (&op->esil, "cf,!,?{,");
		break;
	case ARM_CC_MI:
		close_type = 1;
		r_strbuf_setf (&op->esil, "nf,?{,");
		break;
	case ARM_CC_PL:
		close_type = 1;
		r_strbuf_setf (&op->esil, "nf,!,?{,");
		break;
	case ARM_CC_VS:
		close_type = 1;
		r_strbuf_setf (&op->esil, "vf,?{,");
		break;
	case ARM_CC_VC:
		close_type = 1;
		r_strbuf_setf (&op->esil, "vf,!,?{,");
		break;
	case ARM_CC_HI:
		close_type = 1;
		r_strbuf_setf (&op->esil, "cf,zf,!,&,?{,");
		break;
	case ARM_CC_LS:
		close_type = 1;
		r_strbuf_setf (&op->esil, "cf,!,zf,!,|,?{,");
		break;
	case ARM_CC_GE:
		close_type = 1;
		r_strbuf_setf (&op->esil, "nf,vf,^,!,?{,");
		break;
	case ARM_CC_LT:
		close_type = 1;
		r_strbuf_setf (&op->esil, "nf,vf,^,?{,");
		break;
	case ARM_CC_GT:
		// zf == 0 && nf == vf
		close_type = 1;
		r_strbuf_setf (&op->esil, "zf,!,nf,vf,^,!,&,?{,");
		break;
	case ARM_CC_LE:
		// zf == 1 || nf != vf
		close_type = 1;
		r_strbuf_setf (&op->esil, "zf,nf,vf,^,|,?{,");
		break;
	case ARM_CC_AL:
		// always executed
		break;
	default:
		break;
	}
	return close_cond[close_type];
}