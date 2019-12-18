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
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  UCHARS (size_t) ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intl_convert_utf16_to_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_index_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void collator_convert_hash_item_from_utf16_to_utf8(
	HashTable* hash, zval * hashData, zend_string* hashKey, zend_ulong hashIndex,
	UErrorCode* status )
{
	const char* old_val;
	size_t      old_val_len;
	zend_string* u8str;
	zval        znew_val;

	/* Process string values only. */
	if( Z_TYPE_P( hashData ) != IS_STRING )
		return;

	old_val     = Z_STRVAL_P( hashData );
	old_val_len = Z_STRLEN_P( hashData );

	/* Convert it from UTF-16LE to UTF-8 and save the result to new_val[_len]. */
	u8str = intl_convert_utf16_to_utf8(
		(UChar*)old_val, UCHARS(old_val_len), status );
	if( !u8str )
		return;

	/* Update current hash item with the converted value. */
	ZVAL_NEW_STR( &znew_val, u8str);

	if( hashKey )
	{
		zend_hash_update( hash, hashKey, &znew_val);
	}
	else /* hashKeyType == HASH_KEY_IS_LONG */
	{
		zend_hash_index_update( hash, hashIndex, &znew_val);
	}
}