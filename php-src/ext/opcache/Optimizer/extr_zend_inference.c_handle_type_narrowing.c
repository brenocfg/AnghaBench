#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* vars; } ;
typedef  TYPE_2__ zend_ssa ;
struct TYPE_11__ {TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_12__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_4__ zend_op ;
typedef  int /*<<< orphan*/  zend_bitset ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int definition; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  reset_dependent_vars (TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,char const*) ; 
 char* zend_get_opcode_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_type_narrowing(const zend_op_array *op_array, zend_ssa *ssa, zend_bitset worklist, int var, uint32_t old_type, uint32_t new_type)
{
	if (1) {
		/* Right now, this is always a bug */
		int def_op_num = ssa->vars[var].definition;
		const zend_op *def_opline = def_op_num >= 0 ? &op_array->opcodes[def_op_num] : NULL;
		const char *def_op_name = def_opline ? zend_get_opcode_name(def_opline->opcode) : "PHI";
		zend_error(E_WARNING, "Narrowing occurred during type inference of %s. Please file a bug report on bugs.php.net", def_op_name);
	} else {
		/* if new_type set resets some bits from old_type set
		 * We have completely recalculate types of some dependent SSA variables
		 * (this may occurs mainly because of incremental inter-precudure
		 * type inference)
		 */
		reset_dependent_vars(op_array, ssa, worklist, var);
	}
}