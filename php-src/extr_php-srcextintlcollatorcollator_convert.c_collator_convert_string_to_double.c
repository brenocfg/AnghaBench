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
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * collator_convert_string_to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

zval* collator_convert_string_to_double( zval* str, zval *rv )
{
	zval* num = collator_convert_string_to_number( str, rv );
	if( Z_TYPE_P(num) == IS_LONG )
	{
		ZVAL_DOUBLE( num, Z_LVAL_P( num ) );
	}

	return num;
}