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
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/  const*) ; 
 scalar_t__ ZSTR_VAL (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * php_base64_encode (unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zend_string *php_base64_encode_str(const zend_string *str) {
	return php_base64_encode((const unsigned char*)(ZSTR_VAL(str)), ZSTR_LEN(str));
}