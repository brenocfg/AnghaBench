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
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  use; int /*<<< orphan*/  def; } ;
typedef  TYPE_1__ zend_dfg ;
struct TYPE_6__ {int blocks_count; } ;
typedef  TYPE_2__ zend_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  DFG_BITSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_op_array_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zend_dump_var_set (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 

void zend_dump_dfg(const zend_op_array *op_array, const zend_cfg *cfg, const zend_dfg *dfg)
{
	int j;
	fprintf(stderr, "\nVariable Liveness for \"");
	zend_dump_op_array_name(op_array);
	fprintf(stderr, "\"\n");

	for (j = 0; j < cfg->blocks_count; j++) {
		fprintf(stderr, "  BB%d:\n", j);
		zend_dump_var_set(op_array, "def", DFG_BITSET(dfg->def, dfg->size, j));
		zend_dump_var_set(op_array, "use", DFG_BITSET(dfg->use, dfg->size, j));
		zend_dump_var_set(op_array, "in ", DFG_BITSET(dfg->in,  dfg->size, j));
		zend_dump_var_set(op_array, "out", DFG_BITSET(dfg->out, dfg->size, j));
	}
}