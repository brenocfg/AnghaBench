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
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_TOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKE_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ join_partial_arrays (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ join_partial_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_is_identical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void join_phi_values(zval *a, zval *b, zend_bool escape) {
	if (IS_BOT(a) || IS_TOP(b)) {
		return;
	}
	if (IS_TOP(a)) {
		zval_ptr_dtor_nogc(a);
		ZVAL_COPY(a, b);
		return;
	}
	if (IS_BOT(b)) {
		zval_ptr_dtor_nogc(a);
		MAKE_BOT(a);
		return;
	}
	if (IS_PARTIAL_ARRAY(a) || IS_PARTIAL_ARRAY(b)) {
		if (join_partial_arrays(a, b) != SUCCESS) {
			zval_ptr_dtor_nogc(a);
			MAKE_BOT(a);
		}
	} else if (IS_PARTIAL_OBJECT(a) || IS_PARTIAL_OBJECT(b)) {
		if (escape || join_partial_objects(a, b) != SUCCESS) {
			zval_ptr_dtor_nogc(a);
			MAKE_BOT(a);
		}
	} else if (!zend_is_identical(a, b)) {
		if (join_partial_arrays(a, b) != SUCCESS) {
			zval_ptr_dtor_nogc(a);
			MAKE_BOT(a);
		}
	}
}