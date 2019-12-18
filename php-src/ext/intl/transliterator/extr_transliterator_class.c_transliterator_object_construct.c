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
typedef  int /*<<< orphan*/  zend_string ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  UTransliterator ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;
struct TYPE_2__ {int /*<<< orphan*/ * utrans; } ;
typedef  TYPE_1__ Transliterator_object ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  GC_DELREF (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TRANSLITERATOR_METHOD_FETCH_OBJECT_NO_CHECK ; 
 int /*<<< orphan*/  Transliterator_ce_ptr ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * intl_convert_utf16_to_utf8 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * utrans_getUnicodeID (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  zend_update_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

int transliterator_object_construct( zval *object,
									 UTransliterator *utrans,
									 UErrorCode *status )
{
	const UChar           *ustr_id;
	int32_t               ustr_id_len;
	zend_string           *u8str;
	zval                  tmp;
	Transliterator_object *to;

	TRANSLITERATOR_METHOD_FETCH_OBJECT_NO_CHECK;

	assert( to->utrans == NULL );
	/* this assignment must happen before any return with failure because the
	 * caller relies on it always being made (so it can just destroy the object
	 * to close the transliterator) */
	to->utrans = utrans;

	ustr_id = utrans_getUnicodeID( utrans, &ustr_id_len );
	u8str = intl_convert_utf16_to_utf8(ustr_id, (int ) ustr_id_len, status );
	if( !u8str )
	{
		return FAILURE;
	}

	ZVAL_NEW_STR(&tmp, u8str);
	zend_update_property(Transliterator_ce_ptr, object,
		"id", sizeof( "id" ) - 1, &tmp );
	GC_DELREF(u8str);
	return SUCCESS;
}