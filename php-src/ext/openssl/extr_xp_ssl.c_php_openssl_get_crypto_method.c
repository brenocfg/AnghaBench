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
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  php_stream_context ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CRYPTO_IS_CLIENT ; 
 int /*<<< orphan*/ * php_stream_context_get_option (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_long php_openssl_get_crypto_method(
		php_stream_context *ctx, zend_long crypto_method)  /* {{{ */
{
	zval *val;

	if (ctx && (val = php_stream_context_get_option(ctx, "ssl", "crypto_method")) != NULL) {
		crypto_method = zval_get_long(val);
		crypto_method |= STREAM_CRYPTO_IS_CLIENT;
	}

	return crypto_method;
}