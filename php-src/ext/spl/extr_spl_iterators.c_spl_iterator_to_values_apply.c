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
struct TYPE_6__ {TYPE_1__* funcs; } ;
typedef  TYPE_2__ zend_object_iterator ;
struct TYPE_5__ {int /*<<< orphan*/ * (* get_current_data ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_STOP ; 
 int /*<<< orphan*/  Z_TRY_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*) ; 

__attribute__((used)) static int spl_iterator_to_values_apply(zend_object_iterator *iter, void *puser) /* {{{ */
{
	zval *data, *return_value = (zval*)puser;

	data = iter->funcs->get_current_data(iter);
	if (EG(exception)) {
		return ZEND_HASH_APPLY_STOP;
	}
	if (data == NULL) {
		return ZEND_HASH_APPLY_STOP;
	}
	Z_TRY_ADDREF_P(data);
	add_next_index_zval(return_value, data);
	return ZEND_HASH_APPLY_KEEP;
}