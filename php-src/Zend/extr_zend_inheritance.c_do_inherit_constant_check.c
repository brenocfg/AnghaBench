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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_6__ {scalar_t__ ce; } ;
typedef  TYPE_2__ zend_class_constant ;
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_find_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static zend_bool do_inherit_constant_check(HashTable *child_constants_table, zend_class_constant *parent_constant, zend_string *name, const zend_class_entry *iface) /* {{{ */
{
	zval *zv = zend_hash_find_ex(child_constants_table, name, 1);
	zend_class_constant *old_constant;

	if (zv != NULL) {
		old_constant = (zend_class_constant*)Z_PTR_P(zv);
		if (old_constant->ce != parent_constant->ce) {
			zend_error_noreturn(E_COMPILE_ERROR, "Cannot inherit previously-inherited or override constant %s from interface %s", ZSTR_VAL(name), ZSTR_VAL(iface->name));
		}
		return 0;
	}
	return 1;
}