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
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * collator_convert_string_to_number_if_possible (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

zval* collator_convert_string_to_number( zval* str, zval *rv )
{
	zval* num = collator_convert_string_to_number_if_possible( str, rv );
	if( num == str )
	{
		/* String wasn't converted => return zero. */
		zval_ptr_dtor( num );

		num = rv;
		ZVAL_LONG( num, 0 );
	}

	return num;
}