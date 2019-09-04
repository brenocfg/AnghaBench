#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 scalar_t__ IS_INDIRECT ; 
 int /*<<< orphan*/ * Z_INDIRECT_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_unclean_zval_ptr_dtor(zval *zv) /* {{{ */
{
	if (Z_TYPE_P(zv) == IS_INDIRECT) {
		zv = Z_INDIRECT_P(zv);
	}
	i_zval_ptr_dtor(zv);
}