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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imports ; 
 int /*<<< orphan*/ * zend_hash_find_ptr_lc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_bool zend_is_not_imported(zend_string *name) {
	/* Assuming "name" is unqualified here. */
	return !FC(imports)
		|| zend_hash_find_ptr_lc(FC(imports), ZSTR_VAL(name), ZSTR_LEN(name)) == NULL;
}