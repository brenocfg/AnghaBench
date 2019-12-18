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
typedef  int /*<<< orphan*/  zend_type ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_type_factory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void append_type(zval *return_value, zend_type type) {
	zval reflection_type;
	reflection_type_factory(type, &reflection_type, 0);
	zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &reflection_type);
}