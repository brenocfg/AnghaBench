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

/* Variables and functions */
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/ * zend_string_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_string *add_type_string(zend_string *type, zend_string *new_type) {
	zend_string *result;
	if (type == NULL) {
		return zend_string_copy(new_type);
	}

	// TODO: Switch to smart_str?
	result = zend_string_alloc(ZSTR_LEN(type) + ZSTR_LEN(new_type) + 1, 0);
	memcpy(ZSTR_VAL(result), ZSTR_VAL(type), ZSTR_LEN(type));
	ZSTR_VAL(result)[ZSTR_LEN(type)] = '|';
	memcpy(ZSTR_VAL(result) + ZSTR_LEN(type) + 1, ZSTR_VAL(new_type), ZSTR_LEN(new_type));
	ZSTR_VAL(result)[ZSTR_LEN(type) + ZSTR_LEN(new_type) + 1] = '\0';
	zend_string_release(type);
	return result;
}