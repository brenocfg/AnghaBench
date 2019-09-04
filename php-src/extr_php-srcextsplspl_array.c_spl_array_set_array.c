#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_object_get_properties_t ;
typedef  int zend_long ;
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {TYPE_1__* ce; } ;
struct TYPE_9__ {int ar_flags; scalar_t__ ht_iter; int /*<<< orphan*/  array; TYPE_2__ std; } ;
typedef  TYPE_3__ spl_array_object ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_OBJECT ; 
 int SPL_ARRAY_INT_MASK ; 
 int SPL_ARRAY_IS_SELF ; 
 int SPL_ARRAY_USE_OTHER ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_ARR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 TYPE_6__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_HANDLER_P (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_OBJ_HT_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int Z_REFCOUNT_P (int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_properties ; 
 int /*<<< orphan*/  spl_ce_InvalidArgumentException ; 
 int /*<<< orphan*/  spl_handler_ArrayIterator ; 
 int /*<<< orphan*/  spl_handler_ArrayObject ; 
 int /*<<< orphan*/  zend_array_dup (int /*<<< orphan*/ ) ; 
 scalar_t__ zend_std_get_properties ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_array_set_array(zval *object, spl_array_object *intern, zval *array, zend_long ar_flags, int just_array) {
	if (Z_TYPE_P(array) != IS_OBJECT && Z_TYPE_P(array) != IS_ARRAY) {
		zend_throw_exception(spl_ce_InvalidArgumentException, "Passed variable is not an array or object", 0);
		return;
	}

	if (Z_TYPE_P(array) == IS_ARRAY) {
		zval_ptr_dtor(&intern->array);
		if (Z_REFCOUNT_P(array) == 1) {
			ZVAL_COPY(&intern->array, array);
		} else {
			//??? TODO: try to avoid array duplication
			ZVAL_ARR(&intern->array, zend_array_dup(Z_ARR_P(array)));
		}
	} else {
		if (Z_OBJ_HT_P(array) == &spl_handler_ArrayObject || Z_OBJ_HT_P(array) == &spl_handler_ArrayIterator) {
			zval_ptr_dtor(&intern->array);
			if (just_array)	{
				spl_array_object *other = Z_SPLARRAY_P(array);
				ar_flags = other->ar_flags & ~SPL_ARRAY_INT_MASK;
			}
			if (Z_OBJ_P(object) == Z_OBJ_P(array)) {
				ar_flags |= SPL_ARRAY_IS_SELF;
				ZVAL_UNDEF(&intern->array);
			} else {
				ar_flags |= SPL_ARRAY_USE_OTHER;
				ZVAL_COPY(&intern->array, array);
			}
		} else {
			zend_object_get_properties_t handler = Z_OBJ_HANDLER_P(array, get_properties);
			if (handler != zend_std_get_properties) {
				zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0,
					"Overloaded object of type %s is not compatible with %s",
					ZSTR_VAL(Z_OBJCE_P(array)->name), ZSTR_VAL(intern->std.ce->name));
				return;
			}
			zval_ptr_dtor(&intern->array);
			ZVAL_COPY(&intern->array, array);
		}
	}

	intern->ar_flags &= ~SPL_ARRAY_IS_SELF & ~SPL_ARRAY_USE_OTHER;
	intern->ar_flags |= ar_flags;
	intern->ht_iter = (uint32_t)-1;
}