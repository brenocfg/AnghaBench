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
 int ZSTR_LEN (int /*<<< orphan*/  const*) ; 
 char* ZSTR_VAL (int /*<<< orphan*/  const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * zend_string_init (char const*,int,int /*<<< orphan*/ ) ; 

zend_string *php_password_algo_extract_ident(const zend_string* hash) {
	const char *ident, *ident_end;

	if (!hash || ZSTR_LEN(hash) < 3) {
		/* Minimum prefix: "$x$" */
		return NULL;
	}

	ident = ZSTR_VAL(hash) + 1;
	ident_end = strchr(ident, '$');
	if (!ident_end) {
		/* No terminating '$' */
		return NULL;
	}

	return zend_string_init(ident, ident_end - ident, 0);
}