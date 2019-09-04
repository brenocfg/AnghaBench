#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int ce_flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_STR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spl_add_class_name(zval *list, zend_class_entry *pce, int allow, int ce_flags)
{
	if (!allow || (allow > 0 && pce->ce_flags & ce_flags) || (allow < 0 && !(pce->ce_flags & ce_flags))) {
		zval *tmp;

		if ((tmp = zend_hash_find(Z_ARRVAL_P(list), pce->name)) == NULL) {
			zval t;
			ZVAL_STR_COPY(&t, pce->name);
			zend_hash_add(Z_ARRVAL_P(list), pce->name, &t);
		}
	}
}