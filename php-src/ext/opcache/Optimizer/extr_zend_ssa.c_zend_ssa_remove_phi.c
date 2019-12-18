#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t ssa_var; } ;
typedef  TYPE_2__ zend_ssa_phi ;
struct TYPE_12__ {TYPE_1__* vars; } ;
typedef  TYPE_3__ zend_ssa ;
struct TYPE_10__ {scalar_t__ use_chain; int /*<<< orphan*/ * definition_phi; int /*<<< orphan*/ * phi_use_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  zend_ssa_remove_phi_from_block (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_ssa_remove_uses_of_phi_sources (TYPE_3__*,TYPE_2__*) ; 

void zend_ssa_remove_phi(zend_ssa *ssa, zend_ssa_phi *phi) /* {{{ */
{
	ZEND_ASSERT(phi->ssa_var >= 0);
	ZEND_ASSERT(ssa->vars[phi->ssa_var].use_chain < 0
		&& ssa->vars[phi->ssa_var].phi_use_chain == NULL);
	zend_ssa_remove_uses_of_phi_sources(ssa, phi);
	zend_ssa_remove_phi_from_block(ssa, phi);
	ssa->vars[phi->ssa_var].definition_phi = NULL;
	phi->ssa_var = -1;
}