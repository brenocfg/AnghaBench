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
 int /*<<< orphan*/ * collator_convert_string_to_number_if_possible (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * collator_convert_zstr_utf16_to_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

zval* collator_normalize_sort_argument( zval* arg, zval *rv )
{
	zval* n_arg = NULL;

	if( Z_TYPE_P( arg ) != IS_STRING )
	{
		/* If its not a string then nothing to do.
		 * Return original arg.
		 */
		COLLATOR_CONVERT_RETURN_FAILED( arg );
	}

	/* Try convert to number. */
	n_arg = collator_convert_string_to_number_if_possible( arg, rv );

	if( n_arg == arg )
	{
		/* Conversion to number failed. */
		zval_ptr_dtor( n_arg );

		/* Convert string to utf8. */
		n_arg = collator_convert_zstr_utf16_to_utf8( arg, rv );
	}

	return n_arg;
}