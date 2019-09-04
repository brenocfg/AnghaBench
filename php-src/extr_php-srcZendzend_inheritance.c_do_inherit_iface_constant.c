#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_12__ {int type; int /*<<< orphan*/  constants_table; int /*<<< orphan*/  ce_flags; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ zend_class_constant ;

/* Variables and functions */
 scalar_t__ IS_CONSTANT_AST ; 
 int /*<<< orphan*/  ZEND_ACC_CONSTANTS_UPDATED ; 
 int ZEND_INTERNAL_CLASS ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ do_inherit_constant_check (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* pemalloc (int,int) ; 
 int /*<<< orphan*/  zend_hash_update_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void do_inherit_iface_constant(zend_string *name, zend_class_constant *c, zend_class_entry *ce, zend_class_entry *iface) /* {{{ */
{
	if (do_inherit_constant_check(&ce->constants_table, c, name, iface)) {
		zend_class_constant *ct;
		if (Z_TYPE(c->value) == IS_CONSTANT_AST) {
			ce->ce_flags &= ~ZEND_ACC_CONSTANTS_UPDATED;
		}
		if (ce->type & ZEND_INTERNAL_CLASS) {
			ct = pemalloc(sizeof(zend_class_constant), 1);
			memcpy(ct, c, sizeof(zend_class_constant));
			c = ct;
		}
		zend_hash_update_ptr(&ce->constants_table, name, c);
	}
}