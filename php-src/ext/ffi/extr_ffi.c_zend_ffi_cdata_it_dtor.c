#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ zend_ffi_cdata_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_ffi_cdata_it_dtor(zend_object_iterator *iter) /* {{{ */
{
	zval_ptr_dtor(&((zend_ffi_cdata_iterator*)iter)->value);
	zval_ptr_dtor(&iter->data);
}