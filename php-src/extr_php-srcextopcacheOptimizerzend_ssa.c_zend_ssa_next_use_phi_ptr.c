#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pi; size_t block; int* sources; struct TYPE_10__** use_chains; } ;
typedef  TYPE_3__ zend_ssa_phi ;
struct TYPE_8__ {TYPE_2__* blocks; } ;
struct TYPE_11__ {TYPE_1__ cfg; } ;
typedef  TYPE_4__ zend_ssa ;
struct TYPE_9__ {int predecessors_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zend_ssa_phi **zend_ssa_next_use_phi_ptr(zend_ssa *ssa, int var, zend_ssa_phi *p) /* {{{ */
{
	if (p->pi >= 0) {
		return &p->use_chains[0];
	} else {
		int j;
		for (j = 0; j < ssa->cfg.blocks[p->block].predecessors_count; j++) {
			if (p->sources[j] == var) {
				return &p->use_chains[j];
			}
		}
	}
	ZEND_ASSERT(0);
	return NULL;
}