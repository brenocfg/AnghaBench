#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vars_count; TYPE_1__* vars; } ;
typedef  TYPE_2__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ scc; scalar_t__ scc_entry; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CV ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_op_array_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zend_dump_ssa_var (int /*<<< orphan*/  const*,TYPE_2__ const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zend_dump_ssa_variables(const zend_op_array *op_array, const zend_ssa *ssa, uint32_t dump_flags)
{
	int j;

	if (ssa->vars) {
		fprintf(stderr, "\nSSA Variable for \"");
		zend_dump_op_array_name(op_array);
		fprintf(stderr, "\"\n");

		for (j = 0; j < ssa->vars_count; j++) {
			fprintf(stderr, "    ");
			zend_dump_ssa_var(op_array, ssa, j, IS_CV, ssa->vars[j].var, dump_flags);
			if (ssa->vars[j].scc >= 0) {
				if (ssa->vars[j].scc_entry) {
					fprintf(stderr, " *");
				}  else {
					fprintf(stderr, "  ");
				}
				fprintf(stderr, "SCC=%d", ssa->vars[j].scc);
			}
			fprintf(stderr, "\n");
		}
	}
}