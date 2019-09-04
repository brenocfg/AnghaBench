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
 int /*<<< orphan*/  COLLATOR_CONVERT_RETURN_FAILED (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * collator_convert_zstr_utf8_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_make_printable_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

zval* collator_make_printable_zval( zval* arg, zval *rv)
{
	zval arg_copy;
	zval* str    = NULL;

	if( Z_TYPE_P(arg) != IS_STRING )
	{

		int use_copy = zend_make_printable_zval(arg, &arg_copy);

		if( use_copy )
		{
			str = collator_convert_zstr_utf8_to_utf16( &arg_copy, rv );
			zval_ptr_dtor_str( &arg_copy );
		}
		else
		{
			str = collator_convert_zstr_utf8_to_utf16( arg, rv );
		}
	}
	else
	{
		COLLATOR_CONVERT_RETURN_FAILED( arg );
	}

	return str;
}