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
typedef  int zend_long ;
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  mpz_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
#define  IS_FALSE 131 
#define  IS_LONG 130 
#define  IS_STRING 129 
#define  IS_TRUE 128 
 int SUCCESS ; 
 int Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_set_si (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpz_set_str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int convert_to_gmp(mpz_t gmpnumber, zval *val, zend_long base)
{
	switch (Z_TYPE_P(val)) {
	case IS_LONG:
	case IS_FALSE:
	case IS_TRUE: {
		mpz_set_si(gmpnumber, zval_get_long(val));
		return SUCCESS;
	}
	case IS_STRING: {
		char *numstr = Z_STRVAL_P(val);
		zend_bool skip_lead = 0;
		int ret;

		if (Z_STRLEN_P(val) > 2 && numstr[0] == '0') {
			if ((base == 0 || base == 16) && (numstr[1] == 'x' || numstr[1] == 'X')) {
				base = 16;
				skip_lead = 1;
			} else if ((base == 0 || base == 2) && (numstr[1] == 'b' || numstr[1] == 'B')) {
				base = 2;
				skip_lead = 1;
			}
		}

		ret = mpz_set_str(gmpnumber, (skip_lead ? &numstr[2] : numstr), (int) base);
		if (-1 == ret) {
			php_error_docref(NULL, E_WARNING,
				"Unable to convert variable to GMP - string is not an integer");
			return FAILURE;
		}

		return SUCCESS;
	}
	default:
		php_error_docref(NULL, E_WARNING,
			"Unable to convert variable to GMP - wrong type");
		return FAILURE;
	}
}