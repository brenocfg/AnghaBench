#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_7__ {scalar_t__ doc_comment; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ zend_class_constant ;
struct TYPE_8__ {scalar_t__ save_comments; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_SIZE_EX (int) ; 
 int /*<<< orphan*/  ADD_STRING (scalar_t__) ; 
 TYPE_6__ ZCG (int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accel_directives ; 
 int /*<<< orphan*/  zend_persist_zval_calc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_shared_alloc_get_xlat_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_shared_alloc_register_xlat_entry (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void zend_persist_class_constant_calc(zval *zv)
{
	zend_class_constant *c = Z_PTR_P(zv);

	if (!zend_shared_alloc_get_xlat_entry(c)) {
		zend_shared_alloc_register_xlat_entry(c, c);
		ADD_SIZE_EX(sizeof(zend_class_constant));
		zend_persist_zval_calc(&c->value);
		if (ZCG(accel_directives).save_comments && c->doc_comment) {
			ADD_STRING(c->doc_comment);
		}
	}
}