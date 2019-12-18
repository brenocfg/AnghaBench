#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ce_flags; size_t num_interfaces; TYPE_1__* interface_names; struct TYPE_9__** interfaces; int /*<<< orphan*/  parent_name; struct TYPE_9__* parent; } ;
typedef  TYPE_2__ zend_class_entry ;
typedef  int zend_bool ;
typedef  size_t uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/ * lc_name; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ZEND_ACC_LINKED ; 
 int ZEND_ACC_RESOLVED_INTERFACES ; 
 int ZEND_ACC_RESOLVED_PARENT ; 
 int ZEND_FETCH_CLASS_ALLOW_UNLINKED ; 
 int ZEND_FETCH_CLASS_NO_AUTOLOAD ; 
 int instanceof_function (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* zend_lookup_class_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static zend_bool unlinked_instanceof(zend_class_entry *ce1, zend_class_entry *ce2) {
	zend_class_entry *ce;

	if (ce1 == ce2) {
		return 1;
	}

	if (ce1->ce_flags & ZEND_ACC_LINKED) {
		return instanceof_function(ce1, ce2);
	}

	ce = ce1;
	while (ce->parent) {
		if (ce->ce_flags & ZEND_ACC_RESOLVED_PARENT) {
			ce = ce->parent;
		} else {
			ce = zend_lookup_class_ex(ce->parent_name, NULL,
				ZEND_FETCH_CLASS_ALLOW_UNLINKED | ZEND_FETCH_CLASS_NO_AUTOLOAD);
			if (!ce) {
				break;
			}
		}
		if (ce == ce2) {
			return 1;
		}
	}

	if (ce1->num_interfaces) {
		uint32_t i;
		if (ce1->ce_flags & ZEND_ACC_RESOLVED_INTERFACES) {
			/* Unlike the normal instanceof_function(), we have to perform a recursive
			 * check here, as the parent interfaces might not have been fully copied yet. */
			for (i = 0; i < ce1->num_interfaces; i++) {
				if (unlinked_instanceof(ce1->interfaces[i], ce2)) {
					return 1;
				}
			}
		} else {
			for (i = 0; i < ce1->num_interfaces; i++) {
				ce = zend_lookup_class_ex(
					ce1->interface_names[i].name, ce1->interface_names[i].lc_name,
					ZEND_FETCH_CLASS_ALLOW_UNLINKED | ZEND_FETCH_CLASS_NO_AUTOLOAD);
				if (ce && unlinked_instanceof(ce, ce2)) {
					return 1;
				}
			}
		}
	}

	return 0;
}