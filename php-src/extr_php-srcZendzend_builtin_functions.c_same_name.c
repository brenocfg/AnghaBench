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
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int same_name(zend_string *key, zend_string *name) /* {{{ */
{
	zend_string *lcname;
	int ret;

	if (key == name) {
		return 1;
	}
	if (ZSTR_LEN(key) != ZSTR_LEN(name)) {
		return 0;
	}
	lcname = zend_string_tolower(name);
	ret = memcmp(ZSTR_VAL(lcname), ZSTR_VAL(key), ZSTR_LEN(key)) == 0;
	zend_string_release_ex(lcname, 0);
	return ret;
}