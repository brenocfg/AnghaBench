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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  PHP_STREAM_CONTEXT (int /*<<< orphan*/ *) ; 
 long SSL_CTX_get_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  SSL_CTX_set_tmp_rsa_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long SSL_OP_CIPHER_SERVER_PREFERENCE ; 
 long SSL_OP_SINGLE_DH_USE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_openssl_set_server_dh_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ php_openssl_set_server_ecdh_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_openssl_tmp_rsa_cb ; 
 int /*<<< orphan*/ * php_stream_context_get_option (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_openssl_set_server_specific_opts(php_stream *stream, SSL_CTX *ctx) /* {{{ */
{
	zval *zv;
	long ssl_ctx_options = SSL_CTX_get_options(ctx);

#if defined(HAVE_ECDH) && PHP_OPENSSL_API_VERSION < 0x10100
	if (php_openssl_set_server_ecdh_curve(stream, ctx) == FAILURE) {
		return FAILURE;
	}
#endif

#if PHP_OPENSSL_API_VERSION < 0x10100
	SSL_CTX_set_tmp_rsa_callback(ctx, php_openssl_tmp_rsa_cb);
#endif
	/* We now use php_openssl_tmp_rsa_cb to generate a key of appropriate size whenever necessary */
	if (php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "ssl", "rsa_key_size") != NULL) {
		php_error_docref(NULL, E_WARNING, "rsa_key_size context option has been removed");
	}

	php_openssl_set_server_dh_param(stream, ctx);
	zv = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "ssl", "single_dh_use");
	if (zv == NULL || zend_is_true(zv)) {
		ssl_ctx_options |= SSL_OP_SINGLE_DH_USE;
	}

	zv = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "ssl", "honor_cipher_order");
	if (zv == NULL || zend_is_true(zv)) {
		ssl_ctx_options |= SSL_OP_CIPHER_SERVER_PREFERENCE;
	}

	SSL_CTX_set_options(ctx, ssl_ctx_options);

	return SUCCESS;
}