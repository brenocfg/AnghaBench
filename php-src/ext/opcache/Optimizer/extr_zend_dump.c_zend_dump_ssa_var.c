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
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_11__ {TYPE_2__* var_info; TYPE_1__* vars; } ;
typedef  TYPE_3__ zend_ssa ;
struct TYPE_12__ {int last_var; } ;
typedef  TYPE_4__ zend_op_array ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  range; scalar_t__ has_range; } ;
struct TYPE_9__ {scalar_t__ escape_state; scalar_t__ no_val; } ;

/* Variables and functions */
 scalar_t__ ESCAPE_STATE_NO_ESCAPE ; 
 int /*<<< orphan*/  IS_CV ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_range (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_dump_ssa_var_info (TYPE_3__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_dump_var (TYPE_4__ const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zend_dump_ssa_var(const zend_op_array *op_array, const zend_ssa *ssa, int ssa_var_num, zend_uchar var_type, int var_num, uint32_t dump_flags)
{
	if (ssa_var_num >= 0) {
		fprintf(stderr, "#%d.", ssa_var_num);
	} else {
		fprintf(stderr, "#?.");
	}
	zend_dump_var(op_array, (var_num < op_array->last_var ? IS_CV : var_type), var_num);

	if (ssa_var_num >= 0 && ssa->vars) {
		if (ssa->vars[ssa_var_num].no_val) {
			fprintf(stderr, " NOVAL");
		}
		if (ssa->vars[ssa_var_num].escape_state == ESCAPE_STATE_NO_ESCAPE) {
			fprintf(stderr, " NOESC");
		}
		if (ssa->var_info) {
			zend_dump_ssa_var_info(ssa, ssa_var_num, dump_flags);
			if (ssa->var_info[ssa_var_num].has_range) {
				zend_dump_range(&ssa->var_info[ssa_var_num].range);
			}
		}
	}
}