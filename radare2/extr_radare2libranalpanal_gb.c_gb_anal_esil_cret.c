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
typedef  int ut8 ;
struct TYPE_3__ {scalar_t__ cond; int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 scalar_t__ R_ANAL_COND_EQ ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,char) ; 

__attribute__((used)) static inline void gb_anal_esil_cret (RAnalOp *op, const ut8 data)
{
	char cond;
	if ((data & 0xd0) == 0xd0) {
		cond = 'C';
	} else {
		cond = 'Z';
	}
	if (op->cond == R_ANAL_COND_EQ) {
		r_strbuf_setf (&op->esil, "%c,?{,sp,[2],pc,:=,2,sp,+=,}", cond);
	} else {
		r_strbuf_setf (&op->esil, "%c,!,?{,sp,[2],pc,:=,2,sp,+=,}", cond);
	}
}