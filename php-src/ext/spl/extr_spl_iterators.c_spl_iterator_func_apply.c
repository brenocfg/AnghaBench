#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  fcc; int /*<<< orphan*/  fci; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ spl_iterator_apply_info ;

/* Variables and functions */
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_STOP ; 
 int /*<<< orphan*/  zend_fcall_info_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_iterator_func_apply(zend_object_iterator *iter, void *puser) /* {{{ */
{
	zval retval;
	spl_iterator_apply_info  *apply_info = (spl_iterator_apply_info*)puser;
	int result;

	apply_info->count++;
	zend_fcall_info_call(&apply_info->fci, &apply_info->fcc, &retval, NULL);
	result = zend_is_true(&retval) ? ZEND_HASH_APPLY_KEEP : ZEND_HASH_APPLY_STOP;
	zval_ptr_dtor(&retval);
	return result;
}