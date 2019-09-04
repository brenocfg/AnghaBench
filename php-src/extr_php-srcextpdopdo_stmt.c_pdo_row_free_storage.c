#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {TYPE_1__* stmt; } ;
typedef  TYPE_2__ pdo_row_t ;
struct TYPE_3__ {int /*<<< orphan*/  std; int /*<<< orphan*/  lazy_object_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 

void pdo_row_free_storage(zend_object *std)
{
	pdo_row_t *row = (pdo_row_t *)std;
	if (row->stmt) {
		ZVAL_UNDEF(&row->stmt->lazy_object_ref);
		OBJ_RELEASE(&row->stmt->std);
	}
}