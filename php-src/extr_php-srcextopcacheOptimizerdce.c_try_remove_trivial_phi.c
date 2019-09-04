#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pi; int /*<<< orphan*/  ssa_var; } ;
typedef  TYPE_1__ zend_ssa_phi ;
typedef  int /*<<< orphan*/  zend_ssa ;
struct TYPE_8__ {int /*<<< orphan*/ * ssa; } ;
typedef  TYPE_2__ context ;

/* Variables and functions */
 int get_common_phi_source (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ssa_remove_phi (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ssa_rename_var_uses (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void try_remove_trivial_phi(context *ctx, zend_ssa_phi *phi) {
	zend_ssa *ssa = ctx->ssa;
	if (phi->pi < 0) {
		/* Phi assignment with identical source operands */
		int common_source = get_common_phi_source(ssa, phi);
		if (common_source >= 0) {
			zend_ssa_rename_var_uses(ssa, phi->ssa_var, common_source, 1);
			zend_ssa_remove_phi(ssa, phi);
		}
	} else {
		/* Pi assignment that is only used in Phi/Pi assignments */
		// TODO What if we want to rerun type inference after DCE? Maybe separate this?
		/*ZEND_ASSERT(phi->sources[0] != -1);
		if (ssa->vars[phi->ssa_var].use_chain < 0) {
			zend_ssa_rename_var_uses_keep_types(ssa, phi->ssa_var, phi->sources[0], 1);
			zend_ssa_remove_phi(ssa, phi);
		}*/
	}
}