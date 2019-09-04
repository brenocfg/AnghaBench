#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  mpz_ptr ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int FAILURE ; 
 TYPE_1__* GET_GMP_OBJECT_FROM_OBJ (int /*<<< orphan*/ *) ; 
#define  IS_DOUBLE 131 
#define  IS_LONG 130 
#define  IS_STRING 129 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  _IS_NUMBER 128 
 int /*<<< orphan*/  gmp_strval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_fits_slong_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_get_d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_get_si (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmp_cast_object(zend_object *readobj, zval *writeobj, int type) /* {{{ */
{
	mpz_ptr gmpnum;
	switch (type) {
	case IS_STRING:
		gmpnum = GET_GMP_OBJECT_FROM_OBJ(readobj)->num;
		gmp_strval(writeobj, gmpnum, 10);
		return SUCCESS;
	case IS_LONG:
		gmpnum = GET_GMP_OBJECT_FROM_OBJ(readobj)->num;
		ZVAL_LONG(writeobj, mpz_get_si(gmpnum));
		return SUCCESS;
	case IS_DOUBLE:
		gmpnum = GET_GMP_OBJECT_FROM_OBJ(readobj)->num;
		ZVAL_DOUBLE(writeobj, mpz_get_d(gmpnum));
		return SUCCESS;
	case _IS_NUMBER:
		gmpnum = GET_GMP_OBJECT_FROM_OBJ(readobj)->num;
		if (mpz_fits_slong_p(gmpnum)) {
			ZVAL_LONG(writeobj, mpz_get_si(gmpnum));
		} else {
			ZVAL_DOUBLE(writeobj, mpz_get_d(gmpnum));
		}
		return SUCCESS;
	default:
		return FAILURE;
	}
}