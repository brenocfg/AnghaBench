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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_3__ {int /*<<< orphan*/  str_interned; } ;
typedef  TYPE_1__ browscap_parser_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCA_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_ALLOCA_ALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_ALLOCA_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_heap ; 
 int /*<<< orphan*/  zend_hash_add_new_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_new_interned_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_str_tolower_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *browscap_intern_str_ci(
		browscap_parser_ctx *ctx, zend_string *str, zend_bool persistent) {
	zend_string *lcname;
	zend_string *interned;
	ALLOCA_FLAG(use_heap);

	ZSTR_ALLOCA_ALLOC(lcname, ZSTR_LEN(str), use_heap);
	zend_str_tolower_copy(ZSTR_VAL(lcname), ZSTR_VAL(str), ZSTR_LEN(str));
	interned = zend_hash_find_ptr(&ctx->str_interned, lcname);

	if (interned) {
		zend_string_addref(interned);
	} else {
		interned = zend_string_dup(lcname, persistent);
		if (persistent) {
			interned = zend_new_interned_string(interned);
		}
		zend_hash_add_new_ptr(&ctx->str_interned, interned, interned);
	}

	ZSTR_ALLOCA_FREE(lcname, use_heap);
	return interned;
}