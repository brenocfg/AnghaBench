#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_9__ {int /*<<< orphan*/  inf; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ spl_SplObjectStorageElement ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  pos; int /*<<< orphan*/  storage; } ;
typedef  TYPE_3__ spl_SplObjectStorage ;
struct TYPE_11__ {TYPE_1__* iterator_funcs_ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  zf_key; int /*<<< orphan*/  zf_current; int /*<<< orphan*/  zf_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
#define  IS_LONG 129 
#define  IS_STRING 128 
 int IS_TRUE ; 
 int MIT_KEYS_ASSOC ; 
 int MIT_NEED_ALL ; 
 int /*<<< orphan*/  RETURN_FALSE ; 
 int SPL_MULTIPLE_ITERATOR_GET_ALL_CURRENT ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL (int /*<<< orphan*/ ) ; 
 TYPE_5__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR (int /*<<< orphan*/ ) ; 
 int Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  spl_ce_InvalidArgumentException ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  zend_call_method_with_0_params (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_hash_get_current_data_ptr_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_move_forward_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_hash_num_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_symtable_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_multiple_iterator_get_all(spl_SplObjectStorage *intern, int get_type, zval *return_value) /* {{{ */
{
	spl_SplObjectStorageElement *element;
	zval                        *it, retval;
	int                          valid = 1, num_elements;

	num_elements = zend_hash_num_elements(&intern->storage);
	if (num_elements < 1) {
		RETURN_FALSE;
	}

	array_init_size(return_value, num_elements);

	zend_hash_internal_pointer_reset_ex(&intern->storage, &intern->pos);
	while ((element = zend_hash_get_current_data_ptr_ex(&intern->storage, &intern->pos)) != NULL && !EG(exception)) {
		it = &element->obj;
		zend_call_method_with_0_params(Z_OBJ_P(it), Z_OBJCE_P(it), &Z_OBJCE_P(it)->iterator_funcs_ptr->zf_valid, "valid", &retval);

		if (!Z_ISUNDEF(retval)) {
			valid = Z_TYPE(retval) == IS_TRUE;
			zval_ptr_dtor(&retval);
		} else {
			valid = 0;
		}

		if (valid) {
			if (SPL_MULTIPLE_ITERATOR_GET_ALL_CURRENT == get_type) {
				zend_call_method_with_0_params(Z_OBJ_P(it), Z_OBJCE_P(it), &Z_OBJCE_P(it)->iterator_funcs_ptr->zf_current, "current", &retval);
			} else {
				zend_call_method_with_0_params(Z_OBJ_P(it), Z_OBJCE_P(it), &Z_OBJCE_P(it)->iterator_funcs_ptr->zf_key, "key", &retval);
			}
			if (Z_ISUNDEF(retval)) {
				zend_throw_exception(spl_ce_RuntimeException, "Failed to call sub iterator method", 0);
				return;
			}
		} else if (intern->flags & MIT_NEED_ALL) {
			if (SPL_MULTIPLE_ITERATOR_GET_ALL_CURRENT == get_type) {
				zend_throw_exception(spl_ce_RuntimeException, "Called current() with non valid sub iterator", 0);
			} else {
				zend_throw_exception(spl_ce_RuntimeException, "Called key() with non valid sub iterator", 0);
			}
			return;
		} else {
			ZVAL_NULL(&retval);
		}

		if (intern->flags & MIT_KEYS_ASSOC) {
			switch (Z_TYPE(element->inf)) {
				case IS_LONG:
					add_index_zval(return_value, Z_LVAL(element->inf), &retval);
					break;
				case IS_STRING:
					zend_symtable_update(Z_ARRVAL_P(return_value), Z_STR(element->inf), &retval);
					break;
				default:
					zval_ptr_dtor(&retval);
					zend_throw_exception(spl_ce_InvalidArgumentException, "Sub-Iterator is associated with NULL", 0);
					return;
			}
		} else {
			add_next_index_zval(return_value, &retval);
		}

		zend_hash_move_forward_ex(&intern->storage, &intern->pos);
	}
}