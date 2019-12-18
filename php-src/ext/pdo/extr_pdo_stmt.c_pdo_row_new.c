#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_7__ {TYPE_1__ std; } ;
typedef  TYPE_2__ pdo_row_t ;

/* Variables and functions */
 TYPE_2__* ecalloc (int,int) ; 
 int /*<<< orphan*/  pdo_row_object_handlers ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

zend_object *pdo_row_new(zend_class_entry *ce)
{
	pdo_row_t *row = ecalloc(1, sizeof(pdo_row_t));
	zend_object_std_init(&row->std, ce);
	row->std.handlers = &pdo_row_object_handlers;

	return &row->std;
}