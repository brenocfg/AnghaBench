#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t block; struct TYPE_6__* next; } ;
typedef  TYPE_1__ zend_ssa_phi ;
struct TYPE_7__ {TYPE_1__* phis; } ;
typedef  TYPE_2__ zend_ssa_block ;
struct TYPE_8__ {TYPE_2__* blocks; } ;
typedef  TYPE_3__ zend_ssa ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_ssa_remove_phi_from_block(zend_ssa *ssa, zend_ssa_phi *phi) /* {{{ */
{
	zend_ssa_block *block = &ssa->blocks[phi->block];
	zend_ssa_phi **cur = &block->phis;
	while (*cur != phi) {
		ZEND_ASSERT(*cur != NULL);
		cur = &(*cur)->next;
	}
	*cur = (*cur)->next;
}