#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* cur; } ;
struct TYPE_11__ {int type; TYPE_2__** src; TYPE_2__* dst; } ;
struct TYPE_10__ {int /*<<< orphan*/  memref; } ;
struct TYPE_9__ {char const* arch; } ;
typedef  TYPE_2__ RAnalValue ;
typedef  TYPE_3__ RAnalOp ;
typedef  TYPE_4__ RAnal ;

/* Variables and functions */
 int R_ANAL_OP_TYPE_ADD ; 
#define  R_ANAL_OP_TYPE_CMOV 133 
#define  R_ANAL_OP_TYPE_LEA 132 
#define  R_ANAL_OP_TYPE_LOAD 131 
#define  R_ANAL_OP_TYPE_MOV 130 
#define  R_ANAL_OP_TYPE_POP 129 
 int R_ANAL_OP_TYPE_SUB ; 
#define  R_ANAL_OP_TYPE_XOR 128 
 int /*<<< orphan*/  STR_EQUAL (char const*,char const*) ; 
 int /*<<< orphan*/  is_reg_in_src (char const*,TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static bool is_used_like_arg(const char *regname, const char *opsreg, const char *opdreg, RAnalOp *op, RAnal *anal) {
	#define STR_EQUAL(s1, s2) s1 && s2 && !strcmp (s1, s2)
	RAnalValue *dst = op->dst;
	RAnalValue *src = op->src[0];
	switch (op->type) {
	case R_ANAL_OP_TYPE_POP:
		return false;
	case R_ANAL_OP_TYPE_MOV:
		return (is_reg_in_src (regname, anal, op)) || (STR_EQUAL (opdreg, regname) && dst->memref);
	case R_ANAL_OP_TYPE_CMOV:
		if (STR_EQUAL (opdreg, regname)) {
			return false;
		}
		if (is_reg_in_src (regname, anal, op)) {
			return true;
		}
		return false;
	case R_ANAL_OP_TYPE_LEA:
	case R_ANAL_OP_TYPE_LOAD:
		if (is_reg_in_src (regname, anal, op)) {
			return true;
		}
		if (STR_EQUAL (opdreg, regname)) {
			return false;
		}
    		return false;
	case R_ANAL_OP_TYPE_XOR:
		if (STR_EQUAL (opsreg, opdreg) && !src->memref && !dst->memref) {
			return false;
		}
		//fallthrough
	default:
		if ((op->type == R_ANAL_OP_TYPE_ADD || op->type == R_ANAL_OP_TYPE_SUB) && STR_EQUAL (anal->cur->arch, "arm")) {
			if (STR_EQUAL (opdreg, regname)) {
				return false;
			}
			if (is_reg_in_src (regname, anal, op)) {
				return true;
			}
		}
		return ((STR_EQUAL (opdreg, regname)) || (is_reg_in_src (regname, anal, op)));
	}
}