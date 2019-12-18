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
typedef  int /*<<< orphan*/  zend_serialize_data ;
struct TYPE_3__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_str ;
typedef  int /*<<< orphan*/  php_serialize_data_t ;
typedef  int /*<<< orphan*/  mpz_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  GET_GMP_FROM_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_VAR_SERIALIZE_DESTROY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_VAR_SERIALIZE_INIT (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_ARR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 scalar_t__ estrndup (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gmp_strval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_var_serialize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_std_get_properties (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gmp_serialize(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data) /* {{{ */
{
	mpz_ptr gmpnum = GET_GMP_FROM_ZVAL(object);
	smart_str buf = {0};
	zval zv;
	php_serialize_data_t serialize_data;

	PHP_VAR_SERIALIZE_INIT(serialize_data);

	gmp_strval(&zv, gmpnum, 10);
	php_var_serialize(&buf, &zv, &serialize_data);
	zval_ptr_dtor_str(&zv);

	ZVAL_ARR(&zv, zend_std_get_properties(Z_OBJ_P(object)));
	php_var_serialize(&buf, &zv, &serialize_data);

	PHP_VAR_SERIALIZE_DESTROY(serialize_data);
	*buffer = (unsigned char *) estrndup(ZSTR_VAL(buf.s), ZSTR_LEN(buf.s));
	*buf_len = ZSTR_LEN(buf.s);
	zend_string_release_ex(buf.s, 0);

	return SUCCESS;
}