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
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 int /*<<< orphan*/  COLLATOR_CONVERT_RETURN_FAILED (int /*<<< orphan*/ *) ; 
 int IS_DOUBLE ; 
 int IS_LONG ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  UCHARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int collator_is_numeric (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double*,int) ; 

zval* collator_convert_string_to_number_if_possible( zval* str, zval *rv )
{
	int is_numeric = 0;
	zend_long lval      = 0;
	double dval    = 0;

	if( Z_TYPE_P( str ) != IS_STRING )
	{
		COLLATOR_CONVERT_RETURN_FAILED( str );
	}

	if( ( is_numeric = collator_is_numeric( (UChar*) Z_STRVAL_P(str), UCHARS( Z_STRLEN_P(str) ), &lval, &dval, 1 ) ) )
	{
		if( is_numeric == IS_LONG ) {
			ZVAL_LONG(rv, lval);
		}
		if( is_numeric == IS_DOUBLE )
			ZVAL_DOUBLE(rv, dval);
	}
	else
	{
		COLLATOR_CONVERT_RETURN_FAILED( str );
	}

	return rv;
}