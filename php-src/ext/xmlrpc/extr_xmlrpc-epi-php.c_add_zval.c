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
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ is_numeric_string (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 long strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_index_update (int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_zval(zval* list, const char* id, zval* val)
{
	if (list && val) {
		if (id) {
			int id_len = strlen(id);
			if (!(id_len > 1 && id[0] == '0') && is_numeric_string((char *)id, id_len, NULL, NULL, 0) == IS_LONG) {
				long index = strtol(id, NULL, 0);
				zend_hash_index_update(Z_ARRVAL_P(list), index, val);
			} else {
				zend_hash_str_update(Z_ARRVAL_P(list), (char*)id, strlen(id), val);
			}
		} else {
			zend_hash_next_index_insert(Z_ARRVAL_P(list), val);
		}
	}
}