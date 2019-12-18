#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_6__ {int bits; } ;
struct TYPE_5__ {int size; void* type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_RET ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static inline int hackyArmAnal(RAnal *a, RAnalOp *op, const ut8 *buf, int len) {
	// Hacky support for ARMv8.3
	if (a->bits == 64 && len >= 4) {
		// xpaci // e#43c1da
		if (!memcmp (buf + 1, "\x43\xc1\xda", 3)) {
			op->type = R_ANAL_OP_TYPE_MOV;
			return op->size = 4;
		}
		// retaa
		if (!memcmp (buf, "\xff\x0b\x5f\xd6", 4)) {
			op->type = R_ANAL_OP_TYPE_RET;
			return op->size = 4;
		}
		// retab
		if (!memcmp (buf, "\xff\x0f\x5f\xd6", 4)) {
			op->type = R_ANAL_OP_TYPE_RET;
			return op->size = 4;
		}
	}
	return -1;
}