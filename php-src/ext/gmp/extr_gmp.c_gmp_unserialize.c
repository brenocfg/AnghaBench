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
typedef  int /*<<< orphan*/  zend_unserialize_data ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  int /*<<< orphan*/  php_unserialize_data_t ;
typedef  int /*<<< orphan*/  mpz_ptr ;
typedef  int /*<<< orphan*/  copy_ctor_func_t ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  PHP_VAR_UNSERIALIZE_DESTROY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_VAR_UNSERIALIZE_INIT (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_OBJ_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int convert_to_gmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gmp_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_var_unserialize (int /*<<< orphan*/ *,unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * var_tmp_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_std_get_properties (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zval_add_ref ; 

__attribute__((used)) static int gmp_unserialize(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data) /* {{{ */
{
	mpz_ptr gmpnum;
	const unsigned char *p, *max;
	zval *zv;
	int retval = FAILURE;
	php_unserialize_data_t unserialize_data;
	zend_object *zobj;

	PHP_VAR_UNSERIALIZE_INIT(unserialize_data);
	gmp_create(object, &gmpnum);

	zobj = Z_OBJ_P(object);

	p = buf;
	max = buf + buf_len;

	zv = var_tmp_var(&unserialize_data);
	if (!php_var_unserialize(zv, &p, max, &unserialize_data)
		|| Z_TYPE_P(zv) != IS_STRING
		|| convert_to_gmp(gmpnum, zv, 10) == FAILURE
	) {
		zend_throw_exception(NULL, "Could not unserialize number", 0);
		goto exit;
	}

	zv = var_tmp_var(&unserialize_data);
	if (!php_var_unserialize(zv, &p, max, &unserialize_data)
		|| Z_TYPE_P(zv) != IS_ARRAY
	) {
		zend_throw_exception(NULL, "Could not unserialize properties", 0);
		goto exit;
	}

	if (zend_hash_num_elements(Z_ARRVAL_P(zv)) != 0) {
		zend_hash_copy(
			zend_std_get_properties(zobj), Z_ARRVAL_P(zv),
			(copy_ctor_func_t) zval_add_ref
		);
	}

	retval = SUCCESS;
exit:
	PHP_VAR_UNSERIALIZE_DESTROY(unserialize_data);
	return retval;
}