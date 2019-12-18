#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_9__ {int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_object ;
typedef  int zend_long ;
typedef  int zend_bool ;
struct TYPE_10__ {scalar_t__ fptr_offset_get; scalar_t__ fptr_offset_has; } ;
typedef  TYPE_2__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  BP_VAR_R ; 
 int /*<<< orphan*/  E_WARNING ; 
#define  IS_DOUBLE 134 
#define  IS_FALSE 133 
#define  IS_LONG 132 
 scalar_t__ IS_NULL ; 
#define  IS_REFERENCE 131 
#define  IS_RESOURCE 130 
#define  IS_STRING 129 
#define  IS_TRUE 128 
 int /*<<< orphan*/  SEPARATE_ARG_IF_REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int Z_RES_HANDLE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* spl_array_from_obj (TYPE_1__*) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_2__*) ; 
 int /*<<< orphan*/ * spl_array_read_dimension_ex (int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_call_method_with_1_params (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ *,int) ; 
 int zend_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_symtable_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_array_has_dimension_ex(int check_inherited, zend_object *object, zval *offset, int check_empty) /* {{{ */
{
	spl_array_object *intern = spl_array_from_obj(object);
	zend_long index;
	zval rv, *value = NULL, *tmp;

	if (check_inherited && intern->fptr_offset_has) {
		SEPARATE_ARG_IF_REF(offset);
		zend_call_method_with_1_params(object, object->ce, &intern->fptr_offset_has, "offsetExists", &rv, offset);
		zval_ptr_dtor(offset);

		if (zend_is_true(&rv)) {
			zval_ptr_dtor(&rv);
			if (check_empty != 1) {
				return 1;
			} else if (intern->fptr_offset_get) {
				value = spl_array_read_dimension_ex(1, object, offset, BP_VAR_R, &rv);
			}
		} else {
			zval_ptr_dtor(&rv);
			return 0;
		}
	}

	if (!value) {
		HashTable *ht = spl_array_get_hash_table(intern);

try_again:
		switch (Z_TYPE_P(offset)) {
			case IS_STRING:
				if ((tmp = zend_symtable_find(ht, Z_STR_P(offset))) != NULL) {
					if (check_empty == 2) {
						return 1;
					}
				} else {
					return 0;
				}
				break;

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
				if ((tmp = zend_hash_index_find(ht, index)) != NULL) {
					if (check_empty == 2) {
						return 1;
					}
				} else {
					return 0;
				}
				break;
			case IS_REFERENCE:
				ZVAL_DEREF(offset);
				goto try_again;
			default:
				zend_error(E_WARNING, "Illegal offset type");
				return 0;
		}

		if (check_empty && check_inherited && intern->fptr_offset_get) {
			value = spl_array_read_dimension_ex(1, object, offset, BP_VAR_R, &rv);
		} else {
			value = tmp;
		}
	}

	{
		zend_bool result = check_empty ? zend_is_true(value) : Z_TYPE_P(value) != IS_NULL;
		if (value == &rv) {
			zval_ptr_dtor(&rv);
		}
		return result;
	}
}