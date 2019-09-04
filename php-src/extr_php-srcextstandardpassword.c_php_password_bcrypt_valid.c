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
typedef  int zend_bool ;

/* Variables and functions */
 int ZSTR_LEN (int /*<<< orphan*/  const*) ; 
 char* ZSTR_VAL (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static zend_bool php_password_bcrypt_valid(const zend_string *hash) {
	const char *h = ZSTR_VAL(hash);
	return (ZSTR_LEN(hash) == 60) &&
		(h[0] == '$') && (h[1] == '2') && (h[2] == 'y');
}