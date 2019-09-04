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
struct TYPE_3__ {int /*<<< orphan*/  ce; int /*<<< orphan*/  type_mask; } ;
typedef  TYPE_1__ zend_ssa_type_constraint ;
typedef  int /*<<< orphan*/  zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_type_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_dump_type_constraint(const zend_op_array *op_array, const zend_ssa *ssa, const zend_ssa_type_constraint *constraint, uint32_t dump_flags)
{
	fprintf(stderr, " TYPE");
	zend_dump_type_info(constraint->type_mask, constraint->ce, 1, dump_flags);
}