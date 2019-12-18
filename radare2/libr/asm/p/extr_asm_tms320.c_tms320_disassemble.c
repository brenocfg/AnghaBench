#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_13__ {char* syntax; } ;
struct TYPE_12__ {scalar_t__ cpu; } ;
struct TYPE_11__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  TMS320_F_CPU_C54X ; 
 int /*<<< orphan*/  TMS320_F_CPU_C55X ; 
 int /*<<< orphan*/  TMS320_F_CPU_C55X_PLUS ; 
 TYPE_5__ engine ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_1__*,char*) ; 
 scalar_t__ r_str_casecmp (scalar_t__,char*) ; 
 int tms320_dasm (TYPE_5__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tms320_f_set_cpu (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int tms320c64x_disassemble (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int tms320_disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	if (a->cpu && r_str_casecmp (a->cpu, "c54x") == 0) {
		tms320_f_set_cpu (&engine, TMS320_F_CPU_C54X);
	} else if (a->cpu && r_str_casecmp(a->cpu, "c55x+") == 0) {
		tms320_f_set_cpu (&engine, TMS320_F_CPU_C55X_PLUS);
	} else if (a->cpu && r_str_casecmp(a->cpu, "c55x") == 0) {
		tms320_f_set_cpu (&engine, TMS320_F_CPU_C55X);
	} else {
#if CAPSTONE_HAS_TMS320C64X
		if (a->cpu && !r_str_casecmp (a->cpu, "c64x")) {
			return tms320c64x_disassemble (a, op, buf, len);
		}
#endif
		r_asm_op_set_asm (op, "unknown asm.cpu");
		return op->size = -1;
	}
	op->size = tms320_dasm (&engine, buf, len);
	r_asm_op_set_asm (op, engine.syntax);
	return op->size;
}