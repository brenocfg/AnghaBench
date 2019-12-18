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
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ ) ; 
 int Z_REFCOUNT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_REFVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_bool is_ignorable_reference(HashTable *ht, zval *ref) {
	if (Z_REFCOUNT_P(ref) != 1) {
		return 0;
	}

	/* Directly self-referential arrays are treated as proper references
	 * in zend_array_dup() despite rc=1. */
	return Z_TYPE_P(Z_REFVAL_P(ref)) != IS_ARRAY || Z_ARRVAL_P(Z_REFVAL_P(ref)) != ht;
}