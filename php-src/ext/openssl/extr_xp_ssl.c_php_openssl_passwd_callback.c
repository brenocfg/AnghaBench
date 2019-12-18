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
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  GET_VER_OPT_STRING (char*,char*) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int php_openssl_passwd_callback(char *buf, int num, int verify, void *data) /* {{{ */
{
	php_stream *stream = (php_stream *)data;
	zval *val = NULL;
	char *passphrase = NULL;
	/* TODO: could expand this to make a callback into PHP user-space */

	GET_VER_OPT_STRING("passphrase", passphrase);

	if (passphrase) {
		if (Z_STRLEN_P(val) < (size_t)num - 1) {
			memcpy(buf, Z_STRVAL_P(val), Z_STRLEN_P(val)+1);
			return (int)Z_STRLEN_P(val);
		}
	}
	return 0;
}