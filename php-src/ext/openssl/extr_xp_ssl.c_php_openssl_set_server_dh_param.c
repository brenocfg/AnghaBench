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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int /*<<< orphan*/ * PEM_read_bio_DHparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_OPENSSL_BIO_MODE_R (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_STREAM_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_BINARY ; 
 int /*<<< orphan*/  SSL_CTX_set_dh_auto (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SSL_CTX_set_tmp_dh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * php_stream_context_get_option (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_openssl_set_server_dh_param(php_stream * stream, SSL_CTX *ctx) /* {{{ */
{
	DH *dh;
	BIO* bio;
	zval *zdhpath;

	zdhpath = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "ssl", "dh_param");
	if (zdhpath == NULL) {
#if 0
	/* Coming in OpenSSL 1.1 ... eventually we'll want to enable this
	 * in the absence of an explicit dh_param.
	 */
	SSL_CTX_set_dh_auto(ctx, 1);
#endif
		return SUCCESS;
	}

	if (!try_convert_to_string(zdhpath)) {
		return FAILURE;
	}

	bio = BIO_new_file(Z_STRVAL_P(zdhpath), PHP_OPENSSL_BIO_MODE_R(PKCS7_BINARY));

	if (bio == NULL) {
		php_error_docref(NULL, E_WARNING, "invalid dh_param");
		return FAILURE;
	}

	dh = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
	BIO_free(bio);

	if (dh == NULL) {
		php_error_docref(NULL, E_WARNING, "failed reading DH params");
		return FAILURE;
	}

	if (SSL_CTX_set_tmp_dh(ctx, dh) < 0) {
		php_error_docref(NULL, E_WARNING, "failed assigning DH params");
		DH_free(dh);
		return FAILURE;
	}

	DH_free(dh);

	return SUCCESS;
}