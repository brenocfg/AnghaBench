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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCA_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_ALLOCA_ALLOC (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_ALLOCA_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_heap ; 
 void* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_str_tolower_copy (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static void *zend_hash_find_ptr_lc(HashTable *ht, const char *str, size_t len) {
	void *result;
	zend_string *lcname;
	ALLOCA_FLAG(use_heap);

	ZSTR_ALLOCA_ALLOC(lcname, len, use_heap);
	zend_str_tolower_copy(ZSTR_VAL(lcname), str, len);
	result = zend_hash_find_ptr(ht, lcname);
	ZSTR_ALLOCA_FREE(lcname, use_heap);

	return result;
}