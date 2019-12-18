#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_14__ {int method; TYPE_4__* session; } ;
struct TYPE_16__ {TYPE_3__ inputs; } ;
typedef  TYPE_5__ php_stream_xport_crypto_param ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_13__ {int /*<<< orphan*/  socket; scalar_t__ is_blocked; } ;
struct TYPE_12__ {unsigned char* data; unsigned short len; } ;
struct TYPE_17__ {int is_client; int /*<<< orphan*/ * ssl_handle; TYPE_2__ s; TYPE_1__ alpn_ctx; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_6__ php_openssl_netstream_data_t ;
struct TYPE_15__ {scalar_t__ abstract; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  SSL_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 scalar_t__ GET_VER_OPT (char*) ; 
 int /*<<< orphan*/  GET_VER_OPT_LONG (char*,int) ; 
 int /*<<< orphan*/  GET_VER_OPT_STRING (char*,char*) ; 
 char* OPENSSL_DEFAULT_STREAM_CIPHERS ; 
 scalar_t__ PHP_STREAM_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_CTX_set_alpn_protos (int /*<<< orphan*/ *,unsigned char*,unsigned short) ; 
 int /*<<< orphan*/  SSL_CTX_set_alpn_select_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_default_passwd_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_default_passwd_cb_userdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_min_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_security_level (int /*<<< orphan*/ *,int) ; 
 int SSL_MODE_RELEASE_BUFFERS ; 
 int SSL_OP_ALL ; 
 int SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS ; 
 int SSL_OP_NO_COMPRESSION ; 
 int SSL_OP_NO_TICKET ; 
 int /*<<< orphan*/  SSL_copy_session_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL_get_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSLv23_client_method () ; 
 int /*<<< orphan*/ * SSLv23_server_method () ; 
 int STREAM_CRYPTO_IS_CLIENT ; 
 int SUCCESS ; 
 int /*<<< orphan*/  efree (unsigned char*) ; 
 int /*<<< orphan*/  pefree (unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pestrndup (char const*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 unsigned char* php_openssl_alpn_protos_parse (unsigned short*,char*) ; 
 int /*<<< orphan*/  php_openssl_disable_peer_verification (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_openssl_enable_peer_verification (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_openssl_enable_server_sni (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int php_openssl_get_crypto_method_ctx_flags (int) ; 
 int /*<<< orphan*/  php_openssl_get_max_proto_version (int) ; 
 int /*<<< orphan*/  php_openssl_get_min_proto_version (int) ; 
 int php_openssl_get_proto_version_flags (int,int,int) ; 
 int /*<<< orphan*/  php_openssl_get_ssl_stream_data_index () ; 
 int /*<<< orphan*/  php_openssl_handle_ssl_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_openssl_init_server_reneg_limit (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  php_openssl_passwd_callback ; 
 int /*<<< orphan*/  php_openssl_server_alpn_callback ; 
 int php_openssl_set_local_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_openssl_set_server_specific_opts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_openssl_socket_ops ; 
 int /*<<< orphan*/  php_stream_is_persistent (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 
 int zval_get_long (int /*<<< orphan*/ *) ; 

int php_openssl_setup_crypto(php_stream *stream,
		php_openssl_netstream_data_t *sslsock,
		php_stream_xport_crypto_param *cparam) /* {{{ */
{
	const SSL_METHOD *method;
	int ssl_ctx_options;
	int method_flags;
	zend_long min_version = 0;
	zend_long max_version = 0;
	char *cipherlist = NULL;
	char *alpn_protocols = NULL;
	zval *val;

	if (sslsock->ssl_handle) {
		if (sslsock->s.is_blocked) {
			php_error_docref(NULL, E_WARNING, "SSL/TLS already set-up for this stream");
			return FAILURE;
		} else {
			return SUCCESS;
		}
	}

	ERR_clear_error();

	/* We need to do slightly different things based on client/server method
	 * so lets remember which method was selected */
	sslsock->is_client = cparam->inputs.method & STREAM_CRYPTO_IS_CLIENT;
	method_flags = ((cparam->inputs.method >> 1) << 1);

	method = sslsock->is_client ? SSLv23_client_method() : SSLv23_server_method();
	sslsock->ctx = SSL_CTX_new(method);

	GET_VER_OPT_LONG("min_proto_version", min_version);
	GET_VER_OPT_LONG("max_proto_version", max_version);
	method_flags = php_openssl_get_proto_version_flags(method_flags, min_version, max_version);
#if PHP_OPENSSL_API_VERSION < 0x10100
	ssl_ctx_options = php_openssl_get_crypto_method_ctx_flags(method_flags);
#else
	ssl_ctx_options = SSL_OP_ALL;
#endif

	if (sslsock->ctx == NULL) {
		php_error_docref(NULL, E_WARNING, "SSL context creation failure");
		return FAILURE;
	}

	if (GET_VER_OPT("no_ticket") && zend_is_true(val)) {
		ssl_ctx_options |= SSL_OP_NO_TICKET;
	}

	ssl_ctx_options &= ~SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS;

	if (!GET_VER_OPT("disable_compression") || zend_is_true(val)) {
		ssl_ctx_options |= SSL_OP_NO_COMPRESSION;
	}

	if (GET_VER_OPT("verify_peer") && !zend_is_true(val)) {
		php_openssl_disable_peer_verification(sslsock->ctx, stream);
	} else if (FAILURE == php_openssl_enable_peer_verification(sslsock->ctx, stream)) {
		return FAILURE;
	}

	/* callback for the passphrase (for localcert) */
	if (GET_VER_OPT("passphrase")) {
		SSL_CTX_set_default_passwd_cb_userdata(sslsock->ctx, stream);
		SSL_CTX_set_default_passwd_cb(sslsock->ctx, php_openssl_passwd_callback);
	}

	GET_VER_OPT_STRING("ciphers", cipherlist);
#ifndef USE_OPENSSL_SYSTEM_CIPHERS
	if (!cipherlist) {
		cipherlist = OPENSSL_DEFAULT_STREAM_CIPHERS;
	}
#endif
	if (cipherlist) {
		if (SSL_CTX_set_cipher_list(sslsock->ctx, cipherlist) != 1) {
			return FAILURE;
		}
	}

	if (GET_VER_OPT("security_level")) {
#ifdef HAVE_SEC_LEVEL
		zend_long lval = zval_get_long(val);
		if (lval < 0 || lval > 5) {
			php_error_docref(NULL, E_WARNING, "Security level must be between 0 and 5");
		}
		SSL_CTX_set_security_level(sslsock->ctx, lval);
#else
		php_error_docref(NULL, E_WARNING,
				"security_level is not supported by the linked OpenSSL library "
				"- it is supported from version 1.1.0");
#endif
	}

	GET_VER_OPT_STRING("alpn_protocols", alpn_protocols);
	if (alpn_protocols) {
#ifdef HAVE_TLS_ALPN
		{
			unsigned short alpn_len;
			unsigned char *alpn = php_openssl_alpn_protos_parse(&alpn_len, alpn_protocols);

			if (alpn == NULL) {
				php_error_docref(NULL, E_WARNING, "Failed parsing comma-separated TLS ALPN protocol string");
				SSL_CTX_free(sslsock->ctx);
				sslsock->ctx = NULL;
				return FAILURE;
			}
			if (sslsock->is_client) {
				SSL_CTX_set_alpn_protos(sslsock->ctx, alpn, alpn_len);
			} else {
				sslsock->alpn_ctx.data = (unsigned char *) pestrndup((const char*)alpn, alpn_len, php_stream_is_persistent(stream));
				sslsock->alpn_ctx.len = alpn_len;
				SSL_CTX_set_alpn_select_cb(sslsock->ctx, php_openssl_server_alpn_callback, sslsock);
			}

			efree(alpn);
		}
#else
		php_error_docref(NULL, E_WARNING,
			"alpn_protocols support is not compiled into the OpenSSL library against which PHP is linked");
#endif
	}

	if (FAILURE == php_openssl_set_local_cert(sslsock->ctx, stream)) {
		return FAILURE;
	}

	SSL_CTX_set_options(sslsock->ctx, ssl_ctx_options);

#if PHP_OPENSSL_API_VERSION >= 0x10100
	SSL_CTX_set_min_proto_version(sslsock->ctx, php_openssl_get_min_proto_version(method_flags));
	SSL_CTX_set_max_proto_version(sslsock->ctx, php_openssl_get_max_proto_version(method_flags));
#endif

	if (sslsock->is_client == 0 &&
		PHP_STREAM_CONTEXT(stream) &&
		FAILURE == php_openssl_set_server_specific_opts(stream, sslsock->ctx)
	) {
		return FAILURE;
	}

	sslsock->ssl_handle = SSL_new(sslsock->ctx);

	if (sslsock->ssl_handle == NULL) {
		php_error_docref(NULL, E_WARNING, "SSL handle creation failure");
		SSL_CTX_free(sslsock->ctx);
		sslsock->ctx = NULL;
#ifdef HAVE_TLS_ALPN
		if (sslsock->alpn_ctx.data) {
			pefree(sslsock->alpn_ctx.data, php_stream_is_persistent(stream));
			sslsock->alpn_ctx.data = NULL;
		}
#endif
		return FAILURE;
	} else {
		SSL_set_ex_data(sslsock->ssl_handle, php_openssl_get_ssl_stream_data_index(), stream);
	}

	if (!SSL_set_fd(sslsock->ssl_handle, sslsock->s.socket)) {
		php_openssl_handle_ssl_error(stream, 0, 1);
	}

#ifdef HAVE_TLS_SNI
	/* Enable server-side SNI */
	if (!sslsock->is_client && php_openssl_enable_server_sni(stream, sslsock) == FAILURE) {
		return FAILURE;
	}
#endif

	/* Enable server-side handshake renegotiation rate-limiting */
	if (!sslsock->is_client) {
		php_openssl_init_server_reneg_limit(stream, sslsock);
	}

#ifdef SSL_MODE_RELEASE_BUFFERS
	SSL_set_mode(sslsock->ssl_handle, SSL_get_mode(sslsock->ssl_handle) | SSL_MODE_RELEASE_BUFFERS);
#endif

	if (cparam->inputs.session) {
		if (cparam->inputs.session->ops != &php_openssl_socket_ops) {
			php_error_docref(NULL, E_WARNING, "supplied session stream must be an SSL enabled stream");
		} else if (((php_openssl_netstream_data_t*)cparam->inputs.session->abstract)->ssl_handle == NULL) {
			php_error_docref(NULL, E_WARNING, "supplied SSL session stream is not initialized");
		} else {
			SSL_copy_session_id(sslsock->ssl_handle, ((php_openssl_netstream_data_t*)cparam->inputs.session->abstract)->ssl_handle);
		}
	}

	return SUCCESS;
}