#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_long ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  UTransliterator ;
typedef  int /*<<< orphan*/  UTransDirection ;
struct TYPE_3__ {int member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ UParseError ;
typedef  char UChar ;
typedef  int /*<<< orphan*/  Transliterator_object ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TRANSLITERATOR_ERROR_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRANSLITERATOR_ERROR_CODE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ TRANSLITERATOR_FORWARD ; 
 int /*<<< orphan*/  TRANSLITERATOR_METHOD_FETCH_OBJECT_NO_CHECK ; 
 scalar_t__ TRANSLITERATOR_REVERSE ; 
 int /*<<< orphan*/  Transliterator_ce_ptr ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ILLEGAL_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  intl_convert_utf8_to_utf16 (char**,int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_set_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intl_error_set_custom_msg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  transliterator_object_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * utrans_openU (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_transliterator( char *str_id, size_t str_id_len, zend_long direction, zval *object )
{
	Transliterator_object *to;
	UChar	              *ustr_id    = NULL;
	int32_t               ustr_id_len = 0;
	UTransliterator       *utrans;
	UParseError           parse_error   = {0, -1};

	intl_error_reset( NULL );

	if( ( direction != TRANSLITERATOR_FORWARD ) && (direction != TRANSLITERATOR_REVERSE ) )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"transliterator_create: invalid direction", 0 );
		return FAILURE;
	}

	object_init_ex( object, Transliterator_ce_ptr );
	TRANSLITERATOR_METHOD_FETCH_OBJECT_NO_CHECK; /* fetch zend object from zval "object" into "to" */

	/* Convert transliterator id to UTF-16 */
	intl_convert_utf8_to_utf16( &ustr_id, &ustr_id_len, str_id, str_id_len, TRANSLITERATOR_ERROR_CODE_P( to ) );
	if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to ) ) )
	{
		intl_error_set_code( NULL, TRANSLITERATOR_ERROR_CODE( to ) );
		intl_error_set_custom_msg( NULL, "String conversion of id to UTF-16 failed", 0 );
		zval_ptr_dtor( object );
		return FAILURE;
	}

	/* Open ICU Transliterator. */
	utrans = utrans_openU( ustr_id, ustr_id_len, (UTransDirection ) direction,
		NULL, -1, &parse_error, TRANSLITERATOR_ERROR_CODE_P( to ) );
	if (ustr_id) {
		efree( ustr_id );
	}

	if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to ) ) )
	{
		char *buf = NULL;
		intl_error_set_code( NULL, TRANSLITERATOR_ERROR_CODE( to ) );
		spprintf( &buf, 0, "transliterator_create: unable to open ICU transliterator"
			" with id \"%s\"", str_id );
		if( buf == NULL ) {
			intl_error_set_custom_msg( NULL,
				"transliterator_create: unable to open ICU transliterator", 0 );
		}
		else
		{
			intl_error_set_custom_msg( NULL, buf, /* copy message */ 1 );
			efree( buf );
		}
		zval_ptr_dtor( object );
		return FAILURE;
	}

	transliterator_object_construct( object, utrans, TRANSLITERATOR_ERROR_CODE_P( to ) );
	/* no need to close the transliterator manually on construction error */
	if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to ) ) )
	{
		intl_error_set_code( NULL, TRANSLITERATOR_ERROR_CODE( to ) );
		intl_error_set_custom_msg( NULL,
			"transliterator_create: internal constructor call failed", 0 );
		zval_ptr_dtor( object );
		return FAILURE;
	}

	return SUCCESS;
}