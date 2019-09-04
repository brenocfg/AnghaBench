#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int* sources; int pi; int var; int ssa_var; struct TYPE_16__* next; struct TYPE_16__** use_chains; } ;
typedef  TYPE_4__ zend_ssa_phi ;
struct TYPE_15__ {TYPE_2__* blocks; } ;
struct TYPE_17__ {TYPE_3__ cfg; TYPE_1__* blocks; } ;
typedef  TYPE_5__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_18__ {int /*<<< orphan*/  size; int /*<<< orphan*/  use; int /*<<< orphan*/  def; } ;
typedef  TYPE_6__ zend_dfg ;
typedef  int /*<<< orphan*/  zend_arena ;
struct TYPE_14__ {int predecessors_count; } ;
struct TYPE_13__ {TYPE_4__* phis; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ZEND_MM_ALIGNED_SIZE (int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  needs_pi (int /*<<< orphan*/  const*,TYPE_6__*,TYPE_5__*,int,int,int) ; 
 TYPE_4__* zend_arena_calloc (int /*<<< orphan*/ **,int,int) ; 

__attribute__((used)) static zend_ssa_phi *add_pi(
		zend_arena **arena, const zend_op_array *op_array, zend_dfg *dfg, zend_ssa *ssa,
		int from, int to, int var) /* {{{ */
{
	zend_ssa_phi *phi;
	if (!needs_pi(op_array, dfg, ssa, from, to, var)) {
		return NULL;
	}

	phi = zend_arena_calloc(arena, 1,
		ZEND_MM_ALIGNED_SIZE(sizeof(zend_ssa_phi)) +
		ZEND_MM_ALIGNED_SIZE(sizeof(int) * ssa->cfg.blocks[to].predecessors_count) +
		sizeof(void*) * ssa->cfg.blocks[to].predecessors_count);
	phi->sources = (int*)(((char*)phi) + ZEND_MM_ALIGNED_SIZE(sizeof(zend_ssa_phi)));
	memset(phi->sources, 0xff, sizeof(int) * ssa->cfg.blocks[to].predecessors_count);
	phi->use_chains = (zend_ssa_phi**)(((char*)phi->sources) + ZEND_MM_ALIGNED_SIZE(sizeof(int) * ssa->cfg.blocks[to].predecessors_count));

	phi->pi = from;
	phi->var = var;
	phi->ssa_var = -1;
	phi->next = ssa->blocks[to].phis;
	ssa->blocks[to].phis = phi;

	/* Block "to" now defines "var" via the pi statement, so add it to the "def" set. Note that
	 * this is not entirely accurate, because the pi is actually placed along the edge from->to.
	 * If there is a back-edge to "to" this may result in non-minimal SSA form. */
	DFG_SET(dfg->def, dfg->size, to, var);

	/* If there are multiple predecessors in the target block, we need to place a phi there.
	 * However this can (generally) not be expressed in terms of dominance frontiers, so place it
	 * explicitly. dfg->use here really is dfg->phi, we're reusing the set. */
	if (ssa->cfg.blocks[to].predecessors_count > 1) {
		DFG_SET(dfg->use, dfg->size, to, var);
	}

	return phi;
}