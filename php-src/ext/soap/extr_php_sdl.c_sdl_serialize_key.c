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
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_PUT_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSDL_CACHE_PUT_N (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSDL_NO_STRING_MARKER ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdl_serialize_key(zend_string *key, smart_str *out)
{
	if (key) {
		WSDL_CACHE_PUT_INT(ZSTR_LEN(key), out);
		WSDL_CACHE_PUT_N(ZSTR_VAL(key), ZSTR_LEN(key), out);
	} else {
		WSDL_CACHE_PUT_INT(WSDL_NO_STRING_MARKER, out);
	}
}