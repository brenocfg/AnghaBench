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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;
struct TYPE_2__ {scalar_t__ (* cast_object ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const) ;int /*<<< orphan*/ * (* get ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COLLATOR_CONVERT_RETURN_FAILED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
#define  IS_OBJECT 129 
#define  IS_STRING 128 
 int /*<<< orphan*/  UBYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_OBJ_HT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  intl_convert_utf8_to_utf16 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

zval* collator_convert_object_to_string( zval* obj, zval *rv )
{
	zval* zstr        = NULL;
	UErrorCode status = U_ZERO_ERROR;
	UChar* ustr       = NULL;
	int32_t ustr_len  = 0;

	/* Bail out if it's not an object. */
	if( Z_TYPE_P( obj ) != IS_OBJECT )
	{
		COLLATOR_CONVERT_RETURN_FAILED( obj );
	}

	/* Try object's handlers. */
	if( Z_OBJ_HT_P(obj)->get )
	{
		zstr = Z_OBJ_HT_P(obj)->get( Z_OBJ_P(obj), rv );

		switch( Z_TYPE_P( zstr ) )
		{
			case IS_OBJECT:
				{
					/* Bail out. */
					zval_ptr_dtor( zstr );
					COLLATOR_CONVERT_RETURN_FAILED( obj );
				} break;

			case IS_STRING:
				break;

			default:
				{
					convert_to_string( zstr );
				} break;
		}
	}
	else if( Z_OBJ_HT_P(obj)->cast_object )
	{
		zstr = rv;

		if( Z_OBJ_HT_P(obj)->cast_object( Z_OBJ_P(obj), zstr, IS_STRING ) == FAILURE )
		{
			/* cast_object failed => bail out. */
			zval_ptr_dtor( zstr );
			COLLATOR_CONVERT_RETURN_FAILED( obj );
		}
	}

	/* Object wasn't successfully converted => bail out. */
	if( zstr == NULL )
	{
		COLLATOR_CONVERT_RETURN_FAILED( obj );
	}

	/* Convert the string to UTF-16. */
	intl_convert_utf8_to_utf16(
			&ustr, &ustr_len,
			Z_STRVAL_P( zstr ), Z_STRLEN_P( zstr ),
			&status );
	if( U_FAILURE( status ) )
		php_error( E_WARNING, "Error casting object to string in collator_convert_object_to_string()" );

	/* Cleanup zstr to hold utf16 string. */
	zval_ptr_dtor_str( zstr );

	/* Set string. */
	ZVAL_STRINGL( zstr, (char*)ustr, UBYTES(ustr_len));
	//???
	efree((char *)ustr);

	/* Don't free ustr cause it's set in zstr without copy.
	 * efree( ustr );
	 */

	return zstr;
}