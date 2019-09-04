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

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * collator_convert_string_to_double (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numeric_compare_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int collator_numeric_compare_function(zval *result, zval *op1, zval *op2)
{
	zval num1, num2;
	zval *num1_p = NULL;
	zval *num2_p = NULL;

	if( Z_TYPE_P(op1) == IS_STRING )
	{
		num1_p = collator_convert_string_to_double( op1, &num1 );
		op1 = num1_p;
	}

	if( Z_TYPE_P(op2) == IS_STRING )
	{
		num2_p = collator_convert_string_to_double( op2, &num2 );
		op2 = num2_p;
	}

	ZVAL_LONG(result, numeric_compare_function(op1, op2));

	if( num1_p )
		zval_ptr_dtor( num1_p );
	if( num2_p )
		zval_ptr_dtor( num2_p );

	return SUCCESS;
}