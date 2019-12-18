#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_ulong ;
typedef  scalar_t__ zend_uintptr_t ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  scalar_t__ zend_bool ;
typedef  TYPE_1__* php_serialize_data_t ;
struct TYPE_3__ {int n; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 scalar_t__ IS_OBJECT ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_COUNTED_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_ISREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_REFVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_index_add_new (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline zend_long php_add_var_hash(php_serialize_data_t data, zval *var) /* {{{ */
{
	zval *zv;
	zend_ulong key;
	zend_bool is_ref = Z_ISREF_P(var);

	data->n += 1;

	if (!is_ref && Z_TYPE_P(var) != IS_OBJECT) {
		return 0;
	}

	/* References to objects are treated as if the reference didn't exist */
	if (is_ref && Z_TYPE_P(Z_REFVAL_P(var)) == IS_OBJECT) {
		var = Z_REFVAL_P(var);
	}

	/* Index for the variable is stored using the numeric value of the pointer to
	 * the zend_refcounted struct */
	key = (zend_ulong) (zend_uintptr_t) Z_COUNTED_P(var);
	zv = zend_hash_index_find(&data->ht, key);

	if (zv) {
		/* References are only counted once, undo the data->n increment above */
		if (is_ref) {
			data->n -= 1;
		}

		return Z_LVAL_P(zv);
	} else {
		zval zv_n;
		ZVAL_LONG(&zv_n, data->n);
		zend_hash_index_add_new(&data->ht, key, &zv_n);

		/* Additionally to the index, we also store the variable, to ensure that it is
		 * not destroyed during serialization and its pointer reused. The variable is
		 * stored at the numeric value of the pointer + 1, which cannot be the location
		 * of another zend_refcounted structure. */
		zend_hash_index_add_new(&data->ht, key + 1, var);
		Z_ADDREF_P(var);

		return 0;
	}
}