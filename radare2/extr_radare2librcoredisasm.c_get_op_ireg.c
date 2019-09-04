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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {scalar_t__ ireg; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_op_free (TYPE_1__*) ; 
 TYPE_1__* r_core_anal_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (scalar_t__) ; 

__attribute__((used)) static char *get_op_ireg (void *user, ut64 addr) {
	RCore *core = (RCore *)user;
	char *res = NULL;
	RAnalOp *op = r_core_anal_op (core, addr, 0);
	if (op && op->ireg) {
		res = strdup (op->ireg);
	}
	r_anal_op_free (op);
	return res;
}