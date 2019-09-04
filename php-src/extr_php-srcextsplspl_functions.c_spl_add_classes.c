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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {struct TYPE_5__* parent; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  spl_add_class_name (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  spl_add_interfaces (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

int spl_add_classes(zend_class_entry *pce, zval *list, int sub, int allow, int ce_flags)
{
	if (!pce) {
		return 0;
	}
	spl_add_class_name(list, pce, allow, ce_flags);
	if (sub) {
		spl_add_interfaces(list, pce, allow, ce_flags);
		while (pce->parent) {
			pce = pce->parent;
			spl_add_classes(pce, list, sub, allow, ce_flags);
		}
	}
	return 0;
}