#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
struct TYPE_5__ {int is_client; char* url_name; } ;
typedef  TYPE_2__ php_openssl_netstream_data_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int GET_VER_OPT (char*) ; 
 int /*<<< orphan*/  GET_VER_OPT_STRING (char*,char*) ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int SSL_get_verify_result (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
#define  X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT 129 
#define  X509_V_OK 128 
 int /*<<< orphan*/  X509_verify_cert_error_string (int) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ php_openssl_matches_common_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ php_openssl_matches_san_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  php_openssl_x509_fingerprint_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_openssl_apply_peer_verification_policy(SSL *ssl, X509 *peer, php_stream *stream) /* {{{ */
{
	zval *val = NULL;
	zval *peer_fingerprint;
	char *peer_name = NULL;
	int err,
		must_verify_peer,
		must_verify_peer_name,
		must_verify_fingerprint;

	php_openssl_netstream_data_t *sslsock = (php_openssl_netstream_data_t*)stream->abstract;

	must_verify_peer = GET_VER_OPT("verify_peer")
		? zend_is_true(val)
		: sslsock->is_client;

	must_verify_peer_name = GET_VER_OPT("verify_peer_name")
		? zend_is_true(val)
		: sslsock->is_client;

	must_verify_fingerprint = GET_VER_OPT("peer_fingerprint");
	peer_fingerprint = val;

	if ((must_verify_peer || must_verify_peer_name || must_verify_fingerprint) && peer == NULL) {
		php_error_docref(NULL, E_WARNING, "Could not get peer certificate");
		return FAILURE;
	}

	/* Verify the peer against using CA file/path settings */
	if (must_verify_peer) {
		err = SSL_get_verify_result(ssl);
		switch (err) {
			case X509_V_OK:
				/* fine */
				break;
			case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
				if (GET_VER_OPT("allow_self_signed") && zend_is_true(val)) {
					/* allowed */
					break;
				}
				/* not allowed, so fall through */
			default:
				php_error_docref(NULL, E_WARNING,
						"Could not verify peer: code:%d %s",
						err,
						X509_verify_cert_error_string(err)
				);
				return FAILURE;
		}
	}

	/* If a peer_fingerprint match is required this trumps peer and peer_name verification */
	if (must_verify_fingerprint) {
		if (Z_TYPE_P(peer_fingerprint) == IS_STRING || Z_TYPE_P(peer_fingerprint) == IS_ARRAY) {
			if (!php_openssl_x509_fingerprint_match(peer, peer_fingerprint)) {
				php_error_docref(NULL, E_WARNING,
					"peer_fingerprint match failure"
				);
				return FAILURE;
			}
		} else {
			php_error_docref(NULL, E_WARNING,
				"Expected peer fingerprint must be a string or an array"
			);
			return FAILURE;
		}
	}

	/* verify the host name presented in the peer certificate */
	if (must_verify_peer_name) {
		GET_VER_OPT_STRING("peer_name", peer_name);

		/* If no peer name was specified we use the autodetected url name in client environments */
		if (peer_name == NULL && sslsock->is_client) {
			peer_name = sslsock->url_name;
		}

		if (peer_name) {
			if (php_openssl_matches_san_list(peer, peer_name)) {
				return SUCCESS;
			} else if (php_openssl_matches_common_name(peer, peer_name)) {
				return SUCCESS;
			} else {
				return FAILURE;
			}
		} else {
			return FAILURE;
		}
	}

	return SUCCESS;
}