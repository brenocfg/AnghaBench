#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num_interfaces; scalar_t__ type; struct TYPE_8__** interfaces; int /*<<< orphan*/  ce_flags; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ACC_RESOLVED_INTERFACES ; 
 scalar_t__ ZEND_INTERNAL_CLASS ; 
 int /*<<< orphan*/  do_implement_interface (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ erealloc (TYPE_1__**,int) ; 
 scalar_t__ realloc (TYPE_1__**,int) ; 

__attribute__((used)) static void zend_do_inherit_interfaces(zend_class_entry *ce, const zend_class_entry *iface) /* {{{ */
{
	/* expects interface to be contained in ce's interface list already */
	uint32_t i, ce_num, if_num = iface->num_interfaces;
	zend_class_entry *entry;

	ce_num = ce->num_interfaces;

	if (ce->type == ZEND_INTERNAL_CLASS) {
		ce->interfaces = (zend_class_entry **) realloc(ce->interfaces, sizeof(zend_class_entry *) * (ce_num + if_num));
	} else {
		ce->interfaces = (zend_class_entry **) erealloc(ce->interfaces, sizeof(zend_class_entry *) * (ce_num + if_num));
	}

	/* Inherit the interfaces, only if they're not already inherited by the class */
	while (if_num--) {
		entry = iface->interfaces[if_num];
		for (i = 0; i < ce_num; i++) {
			if (ce->interfaces[i] == entry) {
				break;
			}
		}
		if (i == ce_num) {
			ce->interfaces[ce->num_interfaces++] = entry;
		}
	}
	ce->ce_flags |= ZEND_ACC_RESOLVED_INTERFACES;

	/* and now call the implementing handlers */
	while (ce_num < ce->num_interfaces) {
		do_implement_interface(ce, ce->interfaces[ce_num++]);
	}
}