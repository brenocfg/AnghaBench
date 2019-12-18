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
typedef  scalar_t__ zend_ulong ;
typedef  int /*<<< orphan*/  php_stream ;
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 scalar_t__ GET_VER_OPT (char*) ; 
 int /*<<< orphan*/  GET_VER_OPT_LONG (char*,scalar_t__) ; 
 scalar_t__ OPENSSL_DEFAULT_STREAM_VERIFY_DEPTH ; 
 scalar_t__ SSL_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_ex_data_X509_STORE_CTX_idx () ; 
 int X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_CTX_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_V_ERR_CERT_CHAIN_TOO_LONG ; 
 int X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT ; 
 int /*<<< orphan*/  php_openssl_get_ssl_stream_data_index () ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int verify_callback(int preverify_ok, X509_STORE_CTX *ctx) /* {{{ */
{
	php_stream *stream;
	SSL *ssl;
	int err, depth, ret;
	zval *val;
	zend_ulong allowed_depth = OPENSSL_DEFAULT_STREAM_VERIFY_DEPTH;


	ret = preverify_ok;

	/* determine the status for the current cert */
	err = X509_STORE_CTX_get_error(ctx);
	depth = X509_STORE_CTX_get_error_depth(ctx);

	/* conjure the stream & context to use */
	ssl = X509_STORE_CTX_get_ex_data(ctx, SSL_get_ex_data_X509_STORE_CTX_idx());
	stream = (php_stream*)SSL_get_ex_data(ssl, php_openssl_get_ssl_stream_data_index());

	/* if allow_self_signed is set, make sure that verification succeeds */
	if (err == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT &&
		GET_VER_OPT("allow_self_signed") &&
		zend_is_true(val)
	) {
		ret = 1;
	}

	/* check the depth */
	GET_VER_OPT_LONG("verify_depth", allowed_depth);
	if ((zend_ulong)depth > allowed_depth) {
		ret = 0;
		X509_STORE_CTX_set_error(ctx, X509_V_ERR_CERT_CHAIN_TOO_LONG);
	}

	return ret;
}