#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ definition_phi; } ;
typedef  TYPE_2__ zend_ssa_var ;
struct TYPE_7__ {int /*<<< orphan*/  phi_worklist_no_val; int /*<<< orphan*/  phi_dead; TYPE_1__* ssa; } ;
typedef  TYPE_3__ context ;
struct TYPE_5__ {TYPE_2__* vars; } ;

/* Variables and functions */
 scalar_t__ zend_bitset_in (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_incl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void add_to_phi_worklist_no_val(context *ctx, int var_num) {
	zend_ssa_var *var = &ctx->ssa->vars[var_num];
	if (var->definition_phi && zend_bitset_in(ctx->phi_dead, var_num)) {
		zend_bitset_incl(ctx->phi_worklist_no_val, var_num);
	}
}