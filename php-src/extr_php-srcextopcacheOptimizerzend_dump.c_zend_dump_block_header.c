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
struct TYPE_15__ {int /*<<< orphan*/  type; int /*<<< orphan*/  range; } ;
struct TYPE_16__ {scalar_t__ pi; struct TYPE_16__* next; TYPE_3__ constraint; scalar_t__ has_range_constraint; int /*<<< orphan*/  var; int /*<<< orphan*/ * sources; int /*<<< orphan*/  ssa_var; } ;
typedef  TYPE_4__ zend_ssa_phi ;
struct TYPE_17__ {TYPE_1__* blocks; } ;
typedef  TYPE_5__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_18__ {TYPE_2__* blocks; } ;
typedef  TYPE_6__ zend_cfg ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int predecessors_count; } ;
struct TYPE_13__ {TYPE_4__* phis; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_block_info (TYPE_6__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_dump_range_constraint (int /*<<< orphan*/  const*,TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_dump_ssa_var (int /*<<< orphan*/  const*,TYPE_5__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_dump_type_constraint (int /*<<< orphan*/  const*,TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_dump_block_header(const zend_cfg *cfg, const zend_op_array *op_array, const zend_ssa *ssa, int n, uint32_t dump_flags)
{
	zend_dump_block_info(cfg, n, dump_flags);
	if (ssa && ssa->blocks && ssa->blocks[n].phis) {
		zend_ssa_phi *p = ssa->blocks[n].phis;

		do {
			int j;

			fprintf(stderr, "        ");
			zend_dump_ssa_var(op_array, ssa, p->ssa_var, 0, p->var, dump_flags);
			if (p->pi < 0) {
				fprintf(stderr, " = Phi(");
				for (j = 0; j < cfg->blocks[n].predecessors_count; j++) {
					if (j > 0) {
						fprintf(stderr, ", ");
					}
					zend_dump_ssa_var(op_array, ssa, p->sources[j], 0, p->var, dump_flags);
				}
				fprintf(stderr, ")\n");
			} else {
				fprintf(stderr, " = Pi<BB%d>(", p->pi);
				zend_dump_ssa_var(op_array, ssa, p->sources[0], 0, p->var, dump_flags);
				fprintf(stderr, " &");
				if (p->has_range_constraint) {
					zend_dump_range_constraint(op_array, ssa, &p->constraint.range, dump_flags);
				} else {
					zend_dump_type_constraint(op_array, ssa, &p->constraint.type, dump_flags);
				}
				fprintf(stderr, ")\n");
			}
			p = p->next;
		} while (p);
	}
}