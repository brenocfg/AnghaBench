#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_object ;
typedef  int zend_long ;
struct TYPE_9__ {scalar_t__ nApplyCount; scalar_t__ fptr_offset_set; } ;
typedef  TYPE_2__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
#define  IS_DOUBLE 135 
#define  IS_FALSE 134 
#define  IS_LONG 133 
#define  IS_NULL 132 
#define  IS_REFERENCE 131 
#define  IS_RESOURCE 130 
#define  IS_STRING 129 
#define  IS_TRUE 128 
 int /*<<< orphan*/  SEPARATE_ARG_IF_REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int Z_RES_HANDLE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* spl_array_from_obj (TYPE_1__*) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_call_method_with_2_params (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_hash_index_update (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_symtable_update_ind (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_array_write_dimension_ex(int check_inherited, zend_object *object, zval *offset, zval *value) /* {{{ */
{
	spl_array_object *intern = spl_array_from_obj(object);
	zend_long index;
	HashTable *ht;

	if (check_inherited && intern->fptr_offset_set) {
		zval tmp;

		if (!offset) {
			ZVAL_NULL(&tmp);
			offset = &tmp;
		} else {
			SEPARATE_ARG_IF_REF(offset);
		}
		zend_call_method_with_2_params(object, object->ce, &intern->fptr_offset_set, "offsetSet", NULL, offset, value);
		zval_ptr_dtor(offset);
		return;
	}

	if (intern->nApplyCount > 0) {
		zend_error(E_WARNING, "Modification of ArrayObject during sorting is prohibited");
		return;
	}

	Z_TRY_ADDREF_P(value);
	if (!offset) {
		ht = spl_array_get_hash_table(intern);
		zend_hash_next_index_insert(ht, value);
		return;
	}

try_again:
	switch (Z_TYPE_P(offset)) {
		case IS_STRING:
			ht = spl_array_get_hash_table(intern);
			zend_symtable_update_ind(ht, Z_STR_P(offset), value);
			return;
		case IS_DOUBLE:
			index = (zend_long)Z_DVAL_P(offset);
			goto num_index;
		case IS_RESOURCE:
			index = Z_RES_HANDLE_P(offset);
			goto num_index;
		case IS_FALSE:
			index = 0;
			goto num_index;
		case IS_TRUE:
			index = 1;
			goto num_index;
		case IS_LONG:
			index = Z_LVAL_P(offset);
num_index:
			ht = spl_array_get_hash_table(intern);
			zend_hash_index_update(ht, index, value);
			return;
		case IS_NULL:
			ht = spl_array_get_hash_table(intern);
			zend_hash_next_index_insert(ht, value);
			return;
		case IS_REFERENCE:
			ZVAL_DEREF(offset);
			goto try_again;
		default:
			zend_error(E_WARNING, "Illegal offset type");
			zval_ptr_dtor(value);
			return;
	}
}