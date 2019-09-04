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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  UCHARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intl_convert_utf16_to_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*) ; 

zval* collator_convert_zstr_utf16_to_utf8( zval* utf16_zval, zval *rv )
{
	zend_string* u8str;
	UErrorCode status = U_ZERO_ERROR;

	/* Convert to utf8 then. */
	u8str = intl_convert_utf16_to_utf8(
		(UChar*) Z_STRVAL_P(utf16_zval), UCHARS( Z_STRLEN_P(utf16_zval) ), &status );
	if( !u8str ) {
		php_error( E_WARNING, "Error converting utf16 to utf8 in collator_convert_zval_utf16_to_utf8()" );
		ZVAL_EMPTY_STRING( rv );
	} else {
		ZVAL_NEW_STR( rv, u8str );
	}
	return rv;
}