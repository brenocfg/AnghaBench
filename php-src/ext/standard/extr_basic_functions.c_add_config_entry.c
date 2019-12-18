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

/* Variables and functions */
 int GC_FLAGS (int /*<<< orphan*/ *) ; 
 int GC_PERSISTENT ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  ZSTR_IS_INTERNED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_str_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_config_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_index_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_config_entry(zend_ulong h, zend_string *key, zval *entry, zval *retval)
{
	if (Z_TYPE_P(entry) == IS_STRING) {
		zend_string *str = Z_STR_P(entry);
		if (!ZSTR_IS_INTERNED(str)) {
			if (!(GC_FLAGS(str) & GC_PERSISTENT)) {
				zend_string_addref(str);
			} else {
				str = zend_string_init(ZSTR_VAL(str), ZSTR_LEN(str), 0);
			}
		}

		if (key) {
			add_assoc_str_ex(retval, ZSTR_VAL(key), ZSTR_LEN(key), str);
		} else {
			add_index_str(retval, h, str);
		}
	} else if (Z_TYPE_P(entry) == IS_ARRAY) {
		zval tmp;
		array_init(&tmp);
		add_config_entries(Z_ARRVAL_P(entry), &tmp);
		zend_hash_update(Z_ARRVAL_P(retval), key, &tmp);
	}
}