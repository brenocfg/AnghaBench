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
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int NID_X9_62_prime256v1 ; 
 int NID_undef ; 
 int OBJ_sn2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_STREAM_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_ecdh_auto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_tmp_ecdh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * php_stream_context_get_option (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_openssl_set_server_ecdh_curve(php_stream *stream, SSL_CTX *ctx) /* {{{ */
{
	zval *zvcurve;
	int curve_nid;
	EC_KEY *ecdh;

	zvcurve = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "ssl", "ecdh_curve");
	if (zvcurve == NULL) {
#if OPENSSL_VERSION_NUMBER >= 0x10002000L
		SSL_CTX_set_ecdh_auto(ctx, 1);
		return SUCCESS;
#else
		curve_nid = NID_X9_62_prime256v1;
#endif
	} else {
		if (!try_convert_to_string(zvcurve)) {
			return FAILURE;
		}

		curve_nid = OBJ_sn2nid(Z_STRVAL_P(zvcurve));
		if (curve_nid == NID_undef) {
			php_error_docref(NULL, E_WARNING, "invalid ecdh_curve specified");
			return FAILURE;
		}
	}

	ecdh = EC_KEY_new_by_curve_name(curve_nid);
	if (ecdh == NULL) {
		php_error_docref(NULL, E_WARNING, "failed generating ECDH curve");
		return FAILURE;
	}

	SSL_CTX_set_tmp_ecdh(ctx, ecdh);
	EC_KEY_free(ecdh);

	return SUCCESS;
}