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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  UBYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  intl_convert_utf8_to_utf16 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*) ; 

zval* collator_convert_zstr_utf8_to_utf16( zval* utf8_zval, zval *rv )
{
	zval* zstr        = NULL;
	UChar* ustr       = NULL;
	int32_t ustr_len   = 0;
	UErrorCode status = U_ZERO_ERROR;

	/* Convert the string to UTF-16. */
	intl_convert_utf8_to_utf16(
			&ustr, &ustr_len,
			Z_STRVAL_P( utf8_zval ), Z_STRLEN_P( utf8_zval ),
			&status );
	if( U_FAILURE( status ) )
		php_error( E_WARNING, "Error casting object to string in collator_convert_zstr_utf8_to_utf16()" );

	/* Set string. */
	zstr = rv;
	ZVAL_STRINGL( zstr, (char*)ustr, UBYTES(ustr_len));
	//???
	efree((char *)ustr);

	return zstr;
}