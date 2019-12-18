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
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  int /*<<< orphan*/  zend_op_array ;

/* Variables and functions */
 int /*<<< orphan*/  UNSERIALIZE_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_op_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void zend_file_cache_unserialize_func(zval                    *zv,
                                             zend_persistent_script  *script,
                                             void                    *buf)
{
	zend_op_array *op_array;

	UNSERIALIZE_PTR(Z_PTR_P(zv));
	op_array = Z_PTR_P(zv);
	zend_file_cache_unserialize_op_array(op_array, script, buf);
}