#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int last_var; } ;
typedef  TYPE_1__ zend_op_array ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CV ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_op_array_name (TYPE_1__ const*) ; 
 int /*<<< orphan*/  zend_dump_var (TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 

void zend_dump_variables(const zend_op_array *op_array)
{
	int j;

	fprintf(stderr, "\nCV Variables for \"");
	zend_dump_op_array_name(op_array);
	fprintf(stderr, "\"\n");
	for (j = 0; j < op_array->last_var; j++) {
		fprintf(stderr, "    ");
		zend_dump_var(op_array, IS_CV, j);
		fprintf(stderr, "\n");
	}
}