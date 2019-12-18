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
typedef  int /*<<< orphan*/  spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_array_get_pos_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_get_current_key_zval_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void spl_array_iterator_key(zval *object, zval *return_value) /* {{{ */
{
	spl_array_object *intern = Z_SPLARRAY_P(object);
	HashTable *aht = spl_array_get_hash_table(intern);

	zend_hash_get_current_key_zval_ex(aht, return_value, spl_array_get_pos_ptr(aht, intern));
}